def ABC096B() -> int:
    a, b, c = map(int, input().split(' '))
    k = int(input())

    for _ in range(k):
        maximum = max(a, b, c)
        if maximum == a:
            a *= 2
        elif maximum == b:
            b *= 2
        else:
            c *= 2

    return a + b + c

print(ABC096B())