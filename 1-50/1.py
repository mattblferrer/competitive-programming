import math

n = 999

numbers = set()
for i in range(0, math.ceil(n // 3) + 1):
    numbers.add(3 * i)
for i in range(0, math.ceil(n // 5) + 1):
    numbers.add(5 * i)
output = sum(numbers)

print(output)
