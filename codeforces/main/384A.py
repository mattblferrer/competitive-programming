from math import ceil

def problem384A() -> None:
    n = int(input())
    print(ceil(n * n / 2))  # place on same colors on chessboard
    for i in range(n):  # print chessboard with coders
        for j in range(n):
            if i % 2 == j % 2:  # odd row
                print("C", end="")
            else:
                print(".", end="")
        print("")  # new line for formatting

problem384A()