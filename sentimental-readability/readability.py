import re

para = input("Text: ")

letters = 0
words = 0
sentences = 0

for i in para:
    if re.findall("[A-Z]", i.upper()):
        letters += 1
    elif i in ['.', '!', '?']:
        sentences += 1
    elif i == ' ':
        words += 1

# The last word without space
if words > 0:
    words += 1

L = (letters / words) * 100
S = (sentences / words) * 100

index = 0.0588 * L - 0.296 * S - 15.8

if index < 1:
    print("Before Grade 1")
elif index < 16:
    print(f"Grade {round(index)}")
else:
    print("Grade 16+")
