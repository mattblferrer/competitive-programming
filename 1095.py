import sys

def CSES1095() -> int:
    a, b = map(int, sys.stdin.readline().split())
    exp = 1
    mod = 10 ** 9 + 7
    
    for bit in f"{b:32b}": 
        if bit == '1':
            exp = (exp * exp * a) % mod
        else:
            exp = (exp * exp) % mod

    return exp

n = int(input())
for _ in range(n):
    print(CSES1095())