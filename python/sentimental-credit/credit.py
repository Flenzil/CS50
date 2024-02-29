from cs50 import get_int
import re

num = input("Number: ")

checksum = 0

length = len(num)
firstnums = num[:2]

if length < 13 or length > 16 or int(firstnums[0]) < 2 or int(firstnums[0]) > 5:
    print("INVALID")
else:
    n = int(num)
    while n > 0:
        digit = 2 * int(n % 100 / 10)  # Extracts last but one number and doubles

        if digit > 9:
            checksum += 1 + int(digit % 10)
        else:
            checksum += digit

        checksum += int(n % 10)  # Extracts last number and adds to sum
        n = int(n / 100)

    if not int(checksum % 10):
        print(length, firstnums)
        if length == 15 and (firstnums == "34" or firstnums == "37"):
            print("AMEX")

        elif length == 13 and firstnums[0] == "4":
            print("VISA")

        elif length == 16:
            if firstnums[0] == "4":
                print("VISA")

            elif firstnums[0] == "5" and int(firstnums[1]) <= 5 and firstnums[1] != "0":
                print("MASTERCARD")

            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
