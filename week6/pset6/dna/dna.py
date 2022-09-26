import csv
import sys


def main():

    # TODO: Check for command-line usage
    # Need to check there are 3 arguements
    if len(sys.argv) != 3:
        print("Usage: python dna.py DATABASE DNAFILE")

    # We can assume filenames are input in a valid way and as such don't need to error check for validity

    # Set what the database is from the 2nd CLI arguement
    database = sys.argv[1]

    # set what the dnafile is from the 3rd CLI arguement
    dnafile = sys.argv[2]

    # Create a list for dicts to be stored in
    STRlist = []

    # TODO: Read database file into a variable
    # open database file as read only
    with open(database, "r") as file:
        # create a variable to store
        reader = csv.DictReader(file)

        for row in reader:
            STRlist.append(row)

        # print (STRlist)


    # TODO: Read DNA sequence file into a variable
    # open dnafile as read only
    with open(dnafile, "r") as file:
        # read the whole dnafile and store it in 'dnastring'
        dnastring = file.read()

        # print (dnastring)

    # TODO: Find longest match of each STR in DNA sequence

    # get a list of the header values from the dict
    headers = reader.fieldnames
    # print(headers)

    # create empty dict to store repeat values
    dna_repeats = {}

    # loop a number of times equal to the number of headers - 1
    for i in range(len(headers)-1):

        # get the STR value from the dictreader header, and find how many times it consecutively repeats
        STR = headers[i+1]
        # print(STR)
        most_consec_repeats = longest_match(dnastring, STR)
        # print(most_consec_repeats)

        # store the amount STR consecutively repeats in the dna_repeats dict
        dna_repeats[headers[i+1]]=most_consec_repeats

    # print(dna_repeats)

    # TODO: Check database for matching profiles
    for z in range(len(STRlist)):
        matchcount = 0
        # print(STRlist[z])
        for y in range(len(headers)-1):
            # print(STRlist[z][headers[y+1]])
            # print(dna_repeats[headers[y+1]])
            if int(STRlist[z][headers[y+1]]) == int(dna_repeats[headers[y+1]]):
                # print("One STR Matches!")
                matchcount += 1
            else:
                # print("This STR doesn't match, exiting loop")
                break
        if matchcount == len(headers)-1:
            print(STRlist[z][headers[0]])
            exit()

        matchcount = 0

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
