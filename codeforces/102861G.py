n = int(input())
s = 100
h = 100
for i in range(n):
    t = int(input())
    s += t
    h = max(s, h)
print(h)