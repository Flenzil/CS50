from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break


for row in range(height):
    for j in range(height - row - 1, 0, -1):
        print(" ", end="")

    for k in range(row + 1):
        print("#", end="")

    print("  ", end="")

    for l in range(row + 1):
        print("#", end="")

    print()
