a, b = 1, 2
output = 0

while b < 4000000:
    if b % 2 == 0:
        output += b
    a, b = b, a+b

print(output)