x = 0
lines = int(input())

for i in range(lines):
    statement = input()
    if statement == "++X" or statement == "X++":
        x += 1
    elif statement == "--X" or statement == "X--":
        x -= 1
 
print(x)