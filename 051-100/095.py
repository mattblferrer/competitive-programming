# returns the sum of the factors of num
def factors(num):
    factor_sum = 1  # all numbers have a factor of 1

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for factors up to sqrt(n)
        if num % i == 0:
            factor_sum += i
            factor_sum += (num//i)

    return factor_sum


# determines if num is prime
def isprime(num):
    if num % 2 == 0:  # for even numbers
        return False

    for i in range(3, int(num**0.5+1), 2):  # for odd numbers
        if num % i == 0:
            return False
    return True


# declare variables
n = 15473  # given
limit = 1000000
max_chain_length = 5  # given
max_chain = []  # stores the longest possible amicable chain
output = 0  # smallest element of the longest amicable chain

# main loop
while n < limit:
    test_n = factors(n)  # this will be the chain variable
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
                test_n = factors(test_n)
            else:
                break
        else:
            break
    n += 1

# print output
print("The smallest member of the longest amicable chain with no element exceeding {} is {}"
      .format(limit, output))
print("Longest chain: ", max_chain)
print("Length of longest chain: ", max_chain_length)
