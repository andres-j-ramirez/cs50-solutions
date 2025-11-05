from cs50 import get_string

text = get_string("Text: ")

# Calculate level wit Coleman-Liau index:

# Word count
word_count = 1

for char in text:
    if (char == ' '):
        word_count += 1

# Letter count
letter_count = 0

for char in text:
    if (char.isalpha()):
        letter_count += 1

L = float(letter_count) / word_count * 100

# Sentence count
sentence_count = 0

for char in text:
    if (char == '!' or char == '?' or char == '.'):
        sentence_count += 1
S = float(sentence_count) / word_count * 100

# Algorithm
output = round(0.0588 * L - 0.296 * S - 15.8)  # Valid for values 2-15

# Format for eacxh scenario
if output < 2:
    print("Before Grade 1")
elif output >= 16:
    print("Grade 16+")
else:
    print(f"Grade {output}")
