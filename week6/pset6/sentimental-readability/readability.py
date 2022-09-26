from cs50 import get_string

#Get input of line of text from the user and record it in text
text = get_string("Text: ")

#Find out what the length of the string is and record it in length
length = len(text)
print(f"length: {length}")

#find the spaces by counting space characters in text
spaces = text.count(' ') + 1
print(f"spaces: {spaces}")

#find the sentances by counting sentance end characters and adding them all together (probably inefficient way but it's simple!)
sentances = text.count('.') + text.count('?') + text.count('!')
print(f"sentances: {sentances}")

extras = text.count("'") + text.count(',') + text.count('#') + text.count(';')
print(f"extras: {extras}")


#find characters in string by minusing spaces
characters = length - spaces - sentances - extras + 1
print(f"char: {characters}")

lperw = characters/spaces*100
print(lperw)

sperw = sentances/spaces*100
print(sperw)

index = round(0.0588 * lperw - 0.296 * sperw - 15.8)
print(index)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {int(index)}")
