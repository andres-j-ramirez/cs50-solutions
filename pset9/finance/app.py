import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    stocks = db.execute(
        "SELECT stock_symbol, SUM(shares) AS shares FROM purchases WHERE user_id = ? GROUP BY stock_symbol",
        user_id,
    )

    rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = rows[0]["cash"]

    stock_total = 0
    for stock in stocks:
        quote = lookup(stock["stock_symbol"])
        price = quote["price"]

        stock["price"] = price

        stock_total += stock["shares"] * price

    total = stock_total + cash

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("must provide stock symbol", 400)
    if not shares:
        return apology("must provide number of shares", 400)

    try:
        shares = int(shares)
    except ValueError:
        return apology("shares must be an integer", 400)

    if shares <= 0:
        return apology("shares must be a positive integer", 400)

    quote = lookup(symbol)
    if not quote:
        return apology("must enter a valid stock symbol", 400)

    price = quote["price"]
    total = shares * price

    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = rows[0]["cash"]

    if total > cash:
        return apology("Must have enough cash to buy stock(s)", 400)

    db.execute(
        "INSERT INTO purchases (user_id, stock_symbol, shares, price) VALUES (?, ?, ?, ?)",
        session["user_id"], quote["symbol"], shares, price
    )

    db.execute(
        "UPDATE users SET cash = cash - ? WHERE id = ?",
        total, session["user_id"]
    )

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    purchases = db.execute(
        "SELECT stock_symbol, shares, price FROM purchases WHERE user_id = ?", session["user_id"])

    sales = db.execute(
        "SELECT stock_symbol, shares, price FROM sales WHERE user_id = ?", session["user_id"])

    return render_template("history.html", purchases=purchases, sales=sales)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    stocks = [
        {"symbol": "SOND", "name": "Sonder Holdings Inc."},
        {"symbol": "SOXS", "name": "Direxion Daily Semiconductor Bear 3x Shares"},
        {"symbol": "BNKK", "name": "Bonk, Inc. Common Stock"},
        {"symbol": "IVP", "name": "Inspire Veterinary Partners, Inc."},
        {"symbol": "NVDA", "name": "NVIDIA Corporation"},
        {"symbol": "SOXL", "name": "Direxion Daily Semiconductor Bull 3x Shares"},
        {"symbol": "TSLL", "name": "Direxion Shares ETF Trust"},
        {"symbol": "MSTU", "name": "ETF Opportunities Trust T-Rex 2X Long MSTR Daily Target ETF"},
        {"symbol": "TQQQ", "name": "ProShares Trust"},
        {"symbol": "SPY", "name": "SPDR S&P 500"},
        {"symbol": "TSLS", "name": "Direxion Shares ETF Trust"},
        {"symbol": "IBIT", "name": "iShares Bitcoin Trust ETF"},
        {"symbol": "WTO", "name": "UTime Limited"},
        {"symbol": "QQQ", "name": "Invesco QQQ Trust, Series 1"},
        {"symbol": "TSLA", "name": "Tesla, Inc."},
        {"symbol": "ONDS", "name": "Ondas Holdings Inc."},
        {"symbol": "ASST", "name": "Asset Entities Inc."},
        {"symbol": "SGBX", "name": "Safe & Green Holdings Corp."},
        {"symbol": "PLUG", "name": "Plug Power, Inc."},
        {"symbol": "OPEN", "name": "Opendoor Technologies Inc"},
        {"symbol": "IWM", "name": "iShares Russell 2000 ETF"},
        {"symbol": "GOOGL", "name": "Alphabet Inc."},
        {"symbol": "AMD", "name": "Advanced Micro Devices, Inc."},
        {"symbol": "PLTR", "name": "Palantir Technologies Inc."},
        {"symbol": "META", "name": "Meta Platforms, Inc."},
        {"symbol": "GOOG", "name": "Alphabet Inc."},
        {"symbol": "MU", "name": "Micron Technology, Inc."},
        {"symbol": "AAPL", "name": "Apple Inc."},
        {"symbol": "AMZN", "name": "Amazon.com, Inc."},
        {"symbol": "MSFT", "name": "Microsoft Corporation"},
        {"symbol": "AVGO", "name": "Broadcom Inc."},
        {"symbol": "EXAS", "name": "Exact Sciences Corporation"},
        {"symbol": "SNDK", "name": "Sandisk Corporation Common Stock"},
        {"symbol": "VOO", "name": "Vanguard S&P 500 ETF"},
        {"symbol": "HOOD", "name": "Robinhood Markets, Inc."}
    ]

    if request.method == "GET":
        return render_template("quote.html", name="", price="", symbol="", stocks=stocks)
    else:
        symbol = request.form.get("symbol")
        if not lookup(symbol):
            return apology("Stock does not exist", 400)
        name = lookup(symbol)["name"]
        price = lookup(symbol)["price"]
        symbol = lookup(symbol)["symbol"]
        return render_template("quote.html", name=name, price=price, symbol=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords must match", 400)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) == 1:
            return apology("username already taken", 400)

        hash = generate_password_hash(request.form.get("password"))
        new_user = db.execute("INSERT INTO users (username, hash) VALUES(?,?)",
                              request.form.get("username"), hash)

        session["user_id"] = new_user

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "GET":
        stocks = db.execute(
            "SELECT stock_symbol, SUM(shares) AS shares FROM purchases WHERE user_id = ? GROUP BY stock_symbol HAVING shares > 0",
            user_id,
        )
        return render_template("sell.html", stocks=stocks)

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("must provide stock symbol", 400)
    if not shares:
        return apology("must provide number of shares", 400)

    try:
        shares = int(shares)
    except ValueError:
        return apology("shares must be an integer", 400)

    if shares <= 0:
        return apology("shares must be a positive integer", 400)

    rows = db.execute(
        "SELECT COALESCE(SUM(shares), 0) AS shares FROM purchases WHERE user_id = ? AND stock_symbol = ?",
        user_id,
        symbol,
    )
    owned = rows[0]["shares"]

    if owned <= 0:
        return apology("You do not own this stock", 400)

    if shares > owned:
        return apology("You do not have enough shares to sell", 400)

    quote = lookup(symbol)
    if not quote:
        return apology("Stock does not exist", 400)

    price = quote["price"]
    proceeds = shares * price

    db.execute(
        "INSERT INTO purchases (user_id, stock_symbol, shares, price) VALUES (?, ?, ?, ?)",
        user_id,
        symbol,
        -shares,
        price,
    )

    db.execute(
        "UPDATE users SET cash = cash + ? WHERE id = ?",
        proceeds,
        user_id,
    )

    return redirect("/")

