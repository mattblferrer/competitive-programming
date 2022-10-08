# declare variables
limit = 10**7
factorList = [0, 1, 2]  # number of factors of 0, 1, 2
factorList.extend([2]*(limit-2))

# main loop: count all i*j < limit
for i in range(2, limit // 2 + 1):
    for j in range(2, limit // i + 1):
        factorList[i*j] += 1

# count up consecutives
output = sum(1 for i in range(1, limit) if factorList[i] == factorList[i+1])

# print results
print(f"Number of integers for which n and n+1 have the same number of divisors: {output}")
