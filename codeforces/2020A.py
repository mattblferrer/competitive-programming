def problem2020A() -> int:
    n, k = map(int, input().split(' '))
    operations = 0

    if k == 1:
        return n
    
    while n > 0:
        operations += n % k
        n //= k

    return operations

test_cases = int(input())
for _ in range(test_cases):
    print(problem2020A())