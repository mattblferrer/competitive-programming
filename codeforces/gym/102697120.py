from math import gcd

a, b = map(int, input().split("/"))
g = gcd(a, b)
a //= g
b //= g
print(str(a) + "/" + str(b))