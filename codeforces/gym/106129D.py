n = int(input())
points = []
for i in range(n):
    x, y = map(int, input().split())
    points.append((x, y))
 
left = float('inf')
right = 0
top = 0
bot = float('inf')
 
for i in range(n):
    x, y = points[i]
    left = min(left, x)
    right = max(right, x)
    top = max(top, y)
    bot = min(bot, y)
 
print(4)
print(right, top)
print(left, top)
print(left, bot)
print(right, bot)