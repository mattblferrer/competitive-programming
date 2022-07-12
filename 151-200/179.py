# declare variables
limit = 10**7
output = 0
factorList = [1 for i in range(limit+1)]

# main loop: count all i*j < limit
for i in range(2, limit):
    for j in range(1, limit // i + 1):
        factorList[i*j] += 1

# count up consecutives
for i in range(1, limit):
    if factorList[i] == factorList[i+1]:
        output += 1

# print results
print("Number of integers for which n and n+1 have the same number of divisors",
    output)
