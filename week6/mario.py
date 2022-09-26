from sys import argv

if len(argv) == 2:
    def main():
        height = get_height()
        for i in range(height):
            print("#", end="")
        print("")

    def get_height():
        while True:
            try:
                n = int(input("Height: "))
                if n > 0:
                    return n
            except ValueError:
                print("Give me an int!")

    main()

else:
    print("Oh you didn't want to do anything? Silly")
