number = 2**1000  # given number
outputSum = 0

while number > 9:  # 2 or more digits
    lastDigit = number % 10
    outputSum += lastDigit
    number //= 10
outputSum += number  # first digit of number

print(outputSum)
