def problem2009B() -> None:
    n = int(input())
    rows = []
    for _ in range(n):  # get input rows from beatmap
        row = input()
        rows.append(row)

    for row in reversed(rows):  # iterate from bottom row
        print(row.index("#") + 1, end=" ")
    print("")  # print new line for formatting

test_cases = int(input())
for _ in range(test_cases):
    problem2009B()