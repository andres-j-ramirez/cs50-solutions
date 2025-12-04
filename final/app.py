# CS50x 2025 Final Project: Barça Quiz
# This project was developed by Andres Ramirez.
# I used AI-based tools (ChatGPT) to help brainstorm features, debug issues,
# and refine code structure, but I understand and reviewed all code myself.

from flask import Flask, render_template, request, session, redirect
from questions import QUESTIONS, get_question_by_id, choose_next_question
app = Flask(__name__)
app.secret_key = "dev-only-change-me"

@app.route("/", methods=["GET", "POST"])
def index():
    result = None
    finished = False
    question = None
    asked_ids = session.get("asked_ids", [])
    correct = session.get("correct", 0)
    total = session.get("total", 0)

    if request.method == "POST":
        action = request.form.get("action")

        if action == "answer":
            raw_qid = request.form.get("question_id")
            if not raw_qid:
                return redirect("/")
            else:
                qid = int(raw_qid)
                guess = request.form.get("guess", "").strip().lower()

                question = get_question_by_id(qid)
                if question:
                    normalized = guess.lower()
                    is_correct = any(ans in normalized for ans in question["answers"])
                    total += 1
                    result = "correct" if is_correct else "incorrect"
                    correct = (correct + 1) if result == "correct" else correct
                    print("DEBUG score now:", correct, "/", total)

        elif action == "next":
            question = choose_next_question(asked_ids)
            if question is None:
                finished = True
            else:
                asked_ids.append(question["id"])

        elif action == "reset":
            asked_ids = []
            correct = 0
            total = 0
            question = choose_next_question(asked_ids)
            if question is None:
                finished = True
            else:
                asked_ids.append(question["id"])

    if request.method == "GET":
        question = choose_next_question(asked_ids)
        if question is None:
            finished = True
        else:
            asked_ids.append(question["id"])

    session["asked_ids"] = asked_ids
    session["correct"] = correct
    session["total"] = total

    return render_template("index.html", question=question, result=result, finished=finished, correct=correct, total=total)

@app.route("/about")
def about():
    return render_template("about.html")
    

if __name__ == "__main__":
    app.run(debug=True)
