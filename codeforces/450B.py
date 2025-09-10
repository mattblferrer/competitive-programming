def problem450B() -> int:
    x, y = map(int, input().split(' '))
    n = int(input())

    if n % 6 == 1:
        fn = x
    if n % 6 == 2:
        fn = y
    if n % 6 == 3:
        fn = y - x
    if n % 6 == 4:
        fn = -x
    if n % 6 == 5:
        fn = -y
    if n % 6 == 0:
        fn = x - y
    
    return fn % 1000000007

print(problem450B())