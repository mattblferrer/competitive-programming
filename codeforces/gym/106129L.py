t = int(input())
if t <= 360:
    ans = 0
elif t <= 570:
    ans = min(30, t - 360)
elif t <= 585:
    ans = t - 540
else:
    ans = max(45, t - 600)
print(ans)