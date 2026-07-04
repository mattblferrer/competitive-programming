entries = int(input())
prices = [int(x[:-3] + x[-2:]) for x in input().split()]
prices3 = 0
prices4 = 0
total = 0

for price in prices:
    total += price
    mod = price % 5
    if mod <= 2:
        total -= mod
    elif mod == 3:
        prices3 += 1
    elif mod == 4:
        prices4 += 1
    
while prices3:
    if prices4: 
        total -= 2
        prices3 -= 1
        prices4 -= 1
    elif prices3 > 1:
        total -= 1
        prices3 -= 2
    else:
        break

while prices4:
    if prices4 > 2:
        total -= 2
        prices4 -= 3
    else:
        break

print(f"{total/100:.2f}")