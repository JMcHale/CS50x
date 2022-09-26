import csv

typecount = {
    "Blue Spot": 0,
    "HDPE": 0,
    "Waste": 0,
    "PPC": 0
}

with open("prodsheet.csv", "r") as testfile:

    reader = csv.reader(testfile)
    next(reader)
    for row in reader:
        type = row[0]
        print(f"{type}")
        if type in typecount:
            typecount[type] += 1

for key in typecount:
    print(f"{key}: {typecount[key]}")


