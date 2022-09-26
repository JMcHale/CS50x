
#Define the main function
def main():
    #Call the meow function
    meow(5)

#Define the meow function, this can be done after being called, as by the time the compiler has reached "main()", meow has already been defined, as main is always at the end
def meow(n):
    for i in range(n):
        print("meow")

main()