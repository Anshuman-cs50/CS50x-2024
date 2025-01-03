import re


def checksum(card):
    d1 = card[-2::-2]
    d2 = card[-1::-2]

    d1 = [(2 * int(x)) for x in d1]
    d2 = [int(x) for x in d2]

    d1 = [x if x < 10 else (x - 9) for x in d1]

    Lsum = sum(d1) + sum(d2)

    if Lsum % 10 == 0:
        return True
    else:
        return False


card = input("Number: ")


if checksum(card):
    if len(card) == 15:
        # AMEX
        if re.findall("^34.{13}", card) or re.findall("^37.{13}", card):
            print("AMEX")
        else:
            print("INVALID")

    elif len(card) == 16:
        # VISA
        if card[0] == '4':
            print("VISA")

        # MC
        elif re.findall("^[51-55].{14}", card):
            print("MASTERCARD")
        else:
            print("INVALID")

    elif len(card) == 13:
        # VISA
        if re.findall("^4.{12}", card):
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")
else:
    print("INVALID")
