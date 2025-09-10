def problem1612A() -> None:
    def distance(x1: int, y1: int, x2: int, y2: int) -> int:
        return abs(x2 - x1) + abs(y2 - y1)

    x2, y2 = map(int, input().split(" "))
    ab = distance(0, 0, x2, y2)
    if ab % 2 == 1:  # not possible, since ab / 2 will not be an integer
        print(-1, -1)   
    elif x2 <= (ab // 2):
        print(x2, (ab // 2) - x2)
    else:
        print((ab // 2), 0)
    

test_cases = int(input())
for _ in range(test_cases):
    problem1612A()