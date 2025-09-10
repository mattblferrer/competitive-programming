def problem1950B() -> None:
    n = int(input())
    for row_num in range(n):  # print in 2 square tall "rows"
        for _ in range(2):
            for col_num in range(n):
                if row_num % 2 == col_num % 2:
                    print("##", end="")
                else:
                    print("..", end="")
            print("")  # new line

test_cases = int(input())
for _ in range(test_cases):
    problem1950B()