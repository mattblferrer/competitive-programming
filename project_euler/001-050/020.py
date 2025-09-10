def factorial(n):
    fac = 1  # factorial
    for i in range(1, n+1):
        fac *= i
    return fac


# add each digit to sum digitSum
digitSum = sum(int(digit) for digit in str(factorial(100)))  

# print result
print(digitSum)
