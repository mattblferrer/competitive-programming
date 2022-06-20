def factorial(n):
    fac = 1  # factorial
    for i in range(1, n+1):
        fac *= i
    return fac


number = factorial(100)
digitSum = 0
for digit in str(number):  # add each digit to sum digitSum
    digitSum += int(digit)

print(digitSum)
