import csv
from sys import argv, exit

# i use SRT instead of STR just because it was easier not to confuse it with strings


def main():
    # get the fielnames into a list
    with open(argv[1]) as database:
        reader = csv.DictReader(database)
        for row in reader:
            SRT = reader.fieldnames
    # get the number os STR's
    srts = (len(SRT))
    # find the longest run of STR's for each one and store it in a list
    srt = []
    with open(argv[2]) as sample:
        s = sample.read()
        for i in range(srts):
            srt.append(find_srt(s, SRT[i]))
    # check if there's anyone with the same STR's
    match = 0
    find = False
    with open(argv[1]) as database:
        reader = csv.DictReader(database)
        for row in reader:
            for i in range(1, srts):
                if int(row[SRT[i]]) == srt[i]:
                    match += 1
                    if match == srts - 1:
                        print(row["name"])
                        find = True
                        break
                else:
                    match = 0
        # if not found print No match
        if find != True:
            print("No match")
   
# function to get the longest run of one STR


def find_srt(s, sub):
    # initializing the variables to 0
    cur = onestep = count = find = 0
    # checking the legnht of the STR
    key = len(sub)
    # iterating through the string to find the STR
    while find != -1:
        find = s.find(sub, onestep)
        if find >= 0:
            cur += 1
            while True:
                onestep = find + int(key)
                find = s.find(sub, onestep)
                if find == onestep:
                    cur += 1
                    
                elif find > onestep or find == -1:
                    if cur > count:
                        count = cur
                        cur = 0
                    else:
                        cur = 0
                    break

    return count

  
main()