import csv
from cs50 import get_string

#get the variables for name and number for the person
name = get_string("Name: ")
number = get_string("Number: ")

#open the file using with, so it closes after the indented code is run
with open("phonebook.csv", "a") as file:

    #the unique python way of writing to a file, first create the writer object using the csv.writer() function
    writer = csv.writer(file)
    #Then use the method writerow() to write a row with the values [name, number] in them
    writer.writerow([name, number])