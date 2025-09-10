totalSum = 0  # final output
fifthPowers = [0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049]

for i in range(10, 1000000):  # we only have to check numbers up to 7 digits, excluding 1-digit numbers
    sumFifthPowers = 0  # sum of the fifth powers of the digits
    c = i  # check variable

    # computing 5th power sum
    while i > 0:
        j = i % 10
        sumFifthPowers += fifthPowers[j]
        i //= 10

    # check if 5th power sum is equal to the number
    if sumFifthPowers == c:
        totalSum += c

print("The total sum is", totalSum)
