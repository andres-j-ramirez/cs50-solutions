from cs50 import get_int

hashes = get_int("Height: ")

while hashes < 1 or hashes > 8:
    hashes = get_int("Please choose a number between 1 and 8 inclusive: ")

for i in range(hashes):
    print(" " * (hashes - i - 1), end="")
    print("#" * (i + 1),)

