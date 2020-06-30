from cs50 import SQL
from csv import reader
from sys import argv

# open the database
db = SQL("sqlite:///students.db")

# checks the arguments
if len(argv) < 2:
    print("Error")
    exit()

# open the file with the students info
with open(argv[1], newline='') as charactersFile:
    characters = reader(charactersFile)
    for character in characters:
        if character[0] == 'name':
            continue

        # split the full name into first, last and middle name
        fullName = character[0]
        #if the student has no middle name
        if len(fullName) < 3:
            db.execute("INSERT INTO students DISTINCT(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       fullName[0], None, fullName[1], character[1], character[2])

        else:
            db.execute("INSERT INTO students DISTINCT(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       fullName[0], fullName[1], fullName[2], character[1], character[2])