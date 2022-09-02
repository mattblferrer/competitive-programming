from math import prod

def sum_factors(num):  # returns the sum of the factors of num
    check = num
    factors = []

    for i in [2, 3]:  # for 2 and 3
        power = 1
        cFactor = 1

        while num % i == 0:
            cFactor += i**power
            num //= i
            power += 1

        factors.append(cFactor)

    for i in range(6, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        for j in [-1, 1]:  # 6k +- 1
            power = 1
            cFactor = 1
            while num % (i + j) == 0:
                cFactor += (i + j) ** power
                num //= (i + j)
                power += 1

            factors.append(cFactor)

        if num == 1:
            break

    if num != 1:
        factors.append(num+1)

    return prod(factors) - check


# declare variables
n = 15473  # given
limit = 1000000
max_chain_length = 5  # given
max_chain = []  # stores the longest possible amicable chain
output = 0  # smallest element of the longest amicable chain

# main loop
while n < limit:
    test_n = sum_factors(n)  # this will be the chain variable
    current_chain = [n]  # the current n will be initialized in the chain
    isChain = False

    while test_n != 1:  # if 1, then it hit a prime number
        if test_n < limit:  # if it exceeded 1 million
            if test_n == n:  # if chain looped back to the start
                # check for chain length
                if len(current_chain) > max_chain_length:
                    max_chain_length = len(current_chain)
                    max_chain = current_chain
                    output = min(current_chain)

            if test_n not in current_chain:
                current_chain.append(test_n)
                test_n = sum_factors(test_n)
            else:
                break
        else:
            break
    n += 1

# print output
print(f"The smallest member of the longest amicable chain with no element exceeding {limit} is {output}")
print(f"Longest chain: {max_chain}")
print(f"Length of longest chain: {max_chain_length}")
