def CSES1617() -> int:
    n = int(input())
    return pow(2, n, 10**9 + 7)

print(CSES1617())