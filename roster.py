from cs50 import SQL
from sys import argv

# checks for proper arguments, otherwise it exits 
if len(argv) < 2:
    print("usage error, roster.py houseName")
    exit()

# open the database in a variable and then execute a query that list all the people from a particular house in alphabetical order
db = SQL("sqlite:///students.db")
students = db.execute('SELECT  DISTINCT(first), middle, last, birth FROM students ORDER BY last ASC;')

# print each person 
for student in students:
    if student['middle'] != None:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['last']}, born {student['birth']}")