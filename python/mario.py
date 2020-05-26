from cs50 import get_int
# get input from the user
while True:
    n = get_int("Height:")
    # cheking if int is in range
    if n in range(1, 9):
        break
m = n + 1
# printing each row 
for i in range(1, m):
    # print spaces
    print(" " * (n - i), end='')
    # print hashes
    print("#" * i, end='')
    # print two sapces
    print("  ", end='')
    # print hashes
    print("#" * i, end='')
    # printing new line
    print()
