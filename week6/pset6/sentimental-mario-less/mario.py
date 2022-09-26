# TODO
height = 10
while height > 8:
    try:
        height = int(input("Height: "))
    except:
        print("Enter an int!")
while height < 1:
    try:
        height = int(input("Height: "))
    except:
        print("Enter an int!")

spaces = height

for y in range(height):
    for space in range(spaces - 1):
        print(" ", end="")
    for x in range(height + 1 - spaces):
        print("#", end="")
    spaces = spaces - 1
    print("")
