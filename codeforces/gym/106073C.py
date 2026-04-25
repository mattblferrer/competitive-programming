n = int(input())
a = int(''.join(input().split()), 2)
ans = 0
while a != 1:
    ans += 1
    if a % 2 == 1:
        a = a ^ (a * 2)
        a -= 1
    else:
        a //= 2
print(ans)