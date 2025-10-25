k = int(input())
s = input()
ans = 0

while k < int(s, 2):
    for i in range(1, len(s)):
        if s[i] == '1':
            s = s[:i] + s[i + 1:]
            ans += 1
            break
    else:
        s = s[:-1]
        ans += 1

print(ans)