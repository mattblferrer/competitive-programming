def CSES1071() -> int:
    y, x = map(int, input().split(' '))
    loops = max(x, y) - 1 # number of full "loops" around the spiral

    if y < x:  # up-down
        if loops % 2 == 0:  # counterclockwise
            return (loops + 1) ** 2 - y + 1
        else:  # clockwise
            return loops ** 2 + y
    else:  # left-right
        if loops % 2 == 0:  # counterclockwise
            return loops ** 2 + x
        else:  # clockwise
            return (loops + 1) ** 2 - x + 1

test_cases = int(input())
for _ in range(test_cases):
    print(CSES1071())