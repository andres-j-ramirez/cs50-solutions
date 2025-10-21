# Get get_int function from cs50 library
from cs50 import get_int

# Get height of pyramid from user
height = get_int("Height: ")

# Keep prompting until we get input from specifications
while height < 1 or height > 8:
    height = get_int("Choose a height 1-8 inclusive: ")

# Print out a mirrored pyramid with two spaces in between
for i in range(height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))

