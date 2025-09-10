limit = 1000  # given parameter
powerSum = sum(i**i for i in range(1, limit+1))  # calculate power sum

print(f"Power sum: {powerSum % 10**10}")  # print last 10 digits
