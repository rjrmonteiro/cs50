from cs50 import get_string
# get number from the user
number = get_string("Card Number:")
# get the first two digits
firstTwoDigits = int(number[:2])
# inicialize and convert some variables
rest = int(number)
lenght = len(number)
odd = 0
even = 0
# start to iterate through the number
for i in range(lenght - 1): 
    # dealing with the odds
    odd = odd + (rest % 10)
    rest = int(rest / 10)
    # dealing with the evens
    temp = (rest % 10) * 2
    # check to see if the result has two digits
    if (temp) > 9:
        even = (temp % 10) + (int(temp / 10)) + even
        rest = int(rest / 10)
    else:
        even = even + temp
        rest = int(rest / 10)
# creating a checksum
checksum = even + odd
# list of if for each card tipe
if checksum % 10 != 0:
    print("INVALID")

elif (lenght == 13 or lenght == 16) and (40 <= firstTwoDigits <= 49):
    print("VISA")
    
elif lenght == 15 and (firstTwoDigits == 34 or firstTwoDigits == 37):
    print("AMEX")

elif lenght == 16 and (51 <= firstTwoDigits <= 55):
    print("MASTERCARD")
