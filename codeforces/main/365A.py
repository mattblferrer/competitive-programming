def problem365A() -> int:
    def isKGood(n: str, k: int) -> bool:
        seen = set(int(digit) for digit in n)
        for i in range(k + 1):
            if i not in seen:
                return False
        return True

    n, k = map(int, input().split(' '))
    k_good = 0

    for _ in range(n):
        a = input()
        if isKGood(a, k):
            k_good += 1

    return k_good

print(problem365A())