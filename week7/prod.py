import csv

jobnumbers = {}

with open("prodsheet.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        jobnumber = row["Job Number"]

        if jobnumber in jobnumbers:
            jobnumbers[jobnumber] += 1
        else:
            jobnumbers[jobnumber] = 0

print (jobnumbers)