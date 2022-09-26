from cs50 import get_int

try:
    points = int(input("How many points did you lose? "))
except:
    print("That is not an int!")
    exit()

if points < 2:
    print("You lost fewer points than me.")
elif points > 2:
    print("You lost more points than me.")
else:
    print("You lost the same points as me.")
