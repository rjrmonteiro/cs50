from cs50 import get_string
# get text from user
text = get_string("string: ")
# convert text to lower case
text = text.casefold()
# initialize counters
letters = 0
sentences = 0
words = 0
# create alphabet list
Alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
            'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
# count letters
for i in range(0, 26):
    letters = letters + text.count(Alphabet[i])
# count words
words = text.count(" ") + 1
# create symbols list
Symbols = ['!', '.', '?']
# count sentences
for i in range(0, 3):
    sentences = sentences + text.count(Symbols[i])
# create l and s
l = (letters * 100) / words
s = (sentences * 100) / words
# finding Coleman-Liau formula result
grade = round(0.0588 * l - 0.296 * s - 15.8)
# if cases
if grade < 1:
    print("Before Grade 1")
elif 1 <= grade <= 16:
    print("Grade", grade)
else:
    print("Grade 16+")
