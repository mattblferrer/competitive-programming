def problem313A() -> int:
    n = int(input())
    if n > 0:  # no profit from removing from positive
        return n
    return max(int(str(n)[:-1]), int(str(n)[:-2] + str(n)[-1]))

print(problem313A())