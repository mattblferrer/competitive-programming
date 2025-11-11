from math import sqrt

n = int(input())
m = int(input())
k = sqrt(n * n - m * m)
print(m + k)