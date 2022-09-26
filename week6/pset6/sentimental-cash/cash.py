import cs50

#set initial to 0
coins = 0
change = -5

while change < 0:
    change = round(int(cs50.get_float("Change owed: ")*100))

#print(change)

while change > 0:
    while change >= 25:
        coins += 1
        change -= 25
        #print (change)
        #print("Quarter")
    while change >= 10:
        coins += 1
        change -= 10
        #print (change)
        #print("Dime")
    while change >= 5:
        coins += 1
        change -= 5
        #print (change)
        #print("Nickel")
    while change >= 1:
        coins += 1
        change -= 1
        #print (change)
        #print("Cent")



#quarters = 0.25
#dimes = 0.1
#nickels = 0.05
#pennies = 0.01

#dollartimes = 0
#quartertimes = 0
#dimetimes = 0
#pennytimes = 0

#dollars = cs50.get_float("Change owed: ")

#if dollars % 1 == 0:
    #dollartimes = int(dollars / 1)
    #dollars = dollars % 1
    #print(f"Dollars go in: {dollartimes} times")
#else:
    #dollartimes = int(dollars / 1)
    #dollars = dollars % 1
    #print(dollars)

#if dollars % 0.25 <= 0.0001:
    #quartertimes = int(dollars / 0.25)
    #dollars = dollars % 0.25
    #print(f"Dollars go in: {dollartimes} times")
    #print(f"Quarters go in: {quartertimes} times")
#else:
    #quartertimes = int(dollars / 0.25)
    #dollars = dollars % 0.25
    #print(dollars)

#if dollars % 0.1 <= 0.0001:
    #dimetimes = int(dollars / 0.1)
    #dollars = dollars % 0.1
    #print(f"Dollars go in: {dollartimes} times")
    #print(f"Quarters go in: {quartertimes} times")
    #print(f"Dimes go in: {dimetimes} times")
#else:
    #dimetimes = int(dollars / 0.1)
    #dollars = dollars % 0.1
    #print(dollars)

#if dollars % 0.01 <= 0.00001:
    #pennytimes = int(dollars / 0.01)
    #print(f"Dollars go in: {dollartimes} times")
    #print(f"Quarters go in: {quartertimes} times")
    #print(f"Dimes go in: {dimetimes} times")
    #print(f"Pennies go in: {pennytimes} times")

#coins = dollartimes + quartertimes + dimetimes + pennytimes
print(coins)
