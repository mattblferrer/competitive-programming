def problem1183A() -> int:
    n = int(input())
    while True:
        if sum(int(digit) for digit in str(n)) % 4 == 0:
            return n
        n += 1

print(problem1183A())