from cs50 import get_float

# Ask for dollar amount from user
while (True):
    money = get_float("Change owed: ")
    if money >= 0:
        break

# Set up money so it's easier to work with
money = round(money * 100)

# Start the needed totals
quarters = 25
dimes = 10
nickels = 5
pennies = 1

coins = 0

# Figure out the coin distribution
while (money >= quarters):
    money = money - quarters
    coins += 1

while (money >= dimes):
    money = money - dimes
    coins += 1

while (money >= nickels):
    money = money - nickels
    coins += 1

while (money >= pennies):
    money = money - pennies
    coins += 1

print(f"{coins}")

