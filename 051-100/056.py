# given parameters
a = 100
b = 100

# output variables
maximumSum = 0

# iterating through all a, b below limit
for i in range(2, a):
    for j in range(b-i, b):
        num = pow(i, j)
        digitSum = sum([int(digit) for digit in str(num)])

        if digitSum > maximumSum:
            maximumSum = digitSum

# print result
print("The maximum digital sum is", maximumSum)
