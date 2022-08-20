# declare variables
a, b = 2, 8  # start with first two even Fibonacci nums
output = a

# calculate next even Fibonacci
while b < 4000000:
    output += b
    a, b = b, a+4*b

# print result
print(output)
