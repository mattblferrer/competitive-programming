def generateOrdinaryNumbers() -> list[int]:
    ordinary = []
    for length in range(1, 11):
        for digit in range(1, 10):
            ordinary.append(int(str(digit) * length))

    return ordinary

def problem1520B() -> int:
    n = int(input())
    for i, k in enumerate(ordinary):
        if n < k:
            return i

ordinary = generateOrdinaryNumbers()
test_cases = int(input())
for _ in range(test_cases):
    print(problem1520B())