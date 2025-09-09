def problem2028A() -> str:
    n, a, b = map(int, input().split(' '))
    s = input()
    x, y = 0, 0

    for _ in range(20):
        for command in s:
            if (x, y) == (a, b):
                return "YES"
            if command == 'N':
                y += 1
            elif command == 'S':
                y -= 1
            elif command == 'E':
                x += 1
            elif command == 'W':
                x -= 1
        
    return "NO"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2028A())