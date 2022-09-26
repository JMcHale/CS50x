from sys import argv

#finds length of the argv array, to see how many arguements were entered
if len(argv) >= 2:
    print("An arguement!")

    #prints out each arguement put in the command line using a loop! But not the first!
    for arg in argv[1:]:
        print(arg)
else:
    print("Why no arguement????")