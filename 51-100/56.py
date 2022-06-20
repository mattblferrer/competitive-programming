# given parameters
a = 100
b = 100

# output variables
maximumSum = 0

# iterating through all a, b below limit
for i in range(a):
    for j in range(b):
        num = i**j
        digitSum = sum([int(digit) for digit in str(num)])

        if digitSum > maximumSum:
            maximumSum = digitSum

print("The maximum digital sum is", maximumSum)
