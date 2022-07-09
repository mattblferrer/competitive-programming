totalSum = 0  # final output

for i in range(10, 1000000):  # we only have to check numbers up to 7 digits, excluding 1-digit numbers
    digits = [int(digit) for digit in str(i)]
    sumFifthPowers = 0  # sum of the fifth powers of the digits

    # computing 5th power sum
    for j in digits:
        sumFifthPowers += j**5

    # check if 5th power sum is equal to the number
    if sumFifthPowers == i:
        totalSum += i

print("The total sum is", totalSum)
