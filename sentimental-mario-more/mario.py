from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break


def build(h):
    for i in range(1, h+1):
        gap = h - i
        print(" " * gap, end="")
        print("#" * i, end="  ")
        print("#" * i)


build(height)
