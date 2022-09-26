from cs50 import get_string

s = get_string("Do you agree? ")

#You can use a list to check for a conditional, as in a for loop
if s in ["Y","y","Yes","yes"]
    print("Agreed")
#Or even transform it to a lowercase for the check instead
elif s.lower() in ["n", "no"]
    print("Not Agreed")