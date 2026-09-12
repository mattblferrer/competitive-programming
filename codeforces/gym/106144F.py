t = int(input())

for _ in range(t):
    ones = 0
    fulls = 0

    n = int(input())

    for i in range(n):
        row = input()
        new = ""
        for x in row:
            if x != "=":
                new += x

        if new == "xxx":
            fulls += 1
        elif new in ["xx.",".xx"]:
            ones += 1

    if (fulls % 2 == 0) and (ones % 2 == 0):
        print("Polycarp")
    else:
        print("Monocarp")