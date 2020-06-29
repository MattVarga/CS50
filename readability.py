from cs50 import get_string
# gets input
input = get_string("input: ")
# initialized variables to 0
letters = 0
words = 0
sentences = 0
# loops through input to count valid characters
for i in range(len(input)):
    alphabet = list('abcdefghijklmnopqrstuvwxyz')
    # if in alphabet it will index the character count
    if input[i].lower() in alphabet:
        letters += 1
    # counts words
    if (i == 0 and input[i] != ' ') or(i != len(input) - 1 and input[i] == ' ' and input[i + 1] != ' '):
       words += 1
       # counts sentences
    if input[i] == '.' or input[i] == '!' or input[i] == '?':
        sentences += 1

    # calculates the index
    L = (letters / words)* 100
    S = (sentences / words) * 100
    index = (0.0588 * L - 0.296 * S - 15.8)
    
grade = round(index);
# prints / sorts the grade 
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
    
