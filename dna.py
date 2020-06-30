from csv import reader
from csv import DictReader
from sys import argv

#checks the conditon of the input
if len(argv) < 3:
    print("error")
    exit()
# read the sequence from the input file
with open(argv[2]) as samples:
    source = reader(samples)
    for row in source:
        examples = row

gene = examples[0]
sequences = {}
# puts the sequences into a list
with open(argv[1]) as known_examples:
    people = reader(known_examples)
    for row in people:
        genes = row
        genes.pop(0)
        break

for item in genes:
    sequences[item] = 1
# loops through the sequence,and counts repeating sequences
for key in sequences:
    l = len(key)
    tempMax = 0
    temp = 0
    for i in range(len(gene)):
        # after having counted a sequence it skips at the end of it to avoid counting again
        while temp > 0:
            temp -= 1
            continue

        if gene[i: i + l] == key:
            while gene[i - l: i] == gene[i: i + l]:
                temp += 1
                i += l

            # finds the and sets longest sequence
            if temp > tempMax:
                tempMax = temp

    # stores the longest sequence
    sequences[key] += tempMax

# loops through the database of samples so it can compare the sequences
with open(argv[1], newline='') as known_examples:
    people = DictReader(known_examples)
    for person in people:
        match = 0
        for gene in sequences:
            if sequences[gene] == int(person[gene]):
                match += 1
        if match == len(sequences):
            # prints the name of any match
            print(person['name'])
            exit()

    print("No match")