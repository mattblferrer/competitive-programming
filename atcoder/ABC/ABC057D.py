from math import factorial

def ABC057D():
    n, a, b = map(int, input().split())
    v = sorted(list(map(int, input().split())))[::-1]
    sum_v = sum(v[:a])
    mean = sum_v / a
    last = 0
    c = 0
    for i in range(n):
        if v[i] == v[a - 1]:
            last += 1
            if i < a:
                c += 1
    choices = factorial(last) / (factorial(last - c) * factorial(c))
    for i in range(a + 1, b + 1):
        if v[0] == v[i - 1]:
            choices += factorial(last) / (factorial(last - i) * factorial(i))
    print(mean)
    print(int(choices))

ABC057D()