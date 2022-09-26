from cs50 import get_string

#creates a "hash" table or dictionary with a "key", and a "value". The key being the name and the value being the number
phonebook = {
    "Bob": "50505050",
    "Joe": "20328518"
}

#Gets name input
name = get_string("Name to Search: ")

#searches for the "name" variable in the phonebook, assume in the keys???
if name in phonebook:
    #Prints the value in the key that matches "name"
    print(f"Number:{phonebook[name]}")