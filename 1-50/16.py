number = 2**1000  # given number
sum = 0

while number > 9:  # 2 or more digits
    lastDigit = number % 10
    sum += lastDigit
    number //= 10
sum += number  # first digit of number

print(sum)
