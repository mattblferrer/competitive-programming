"""
Length of Farey sequence n = 1 + sum of totient functions from 1 to n
"""


# returns the Mobius function of n
def mobius(n):
    if n == 1:
        return 1
    else:
        factors = 0

        for i in [2, 3]:
            if n % i == 0:  # for 2 and 3
                factors += 1
                n //= i

                if n % i == 0:  # if divisible again
                    return 0

        # only have to check for odd factors up to sqrt(n)
        for i in range(5, int(n ** 0.5) + 1, 6):  
            if n % i == 0:  # 6k-1
                factors += 1
                n //= i

                if n % i == 0:
                    return 0
            if n % (i+2) == 0:  # 6k+1
                factors += 1
                n //= (i+2)

                if n % (i+2) == 0:
                    return 0

        # check if prime
        if n != 1:
            factors += 1

        # check for sign of function result
        if factors % 2 == 0:
            return 1
        else:
            return -1


# declare variables
d = 1000000
totientSum = 1

# main loop
for i in range(1, d+1):
    div = d // i
    totientSum += mobius(i)*div*(1+div)

# print result
print((totientSum - 2)// 2)  # not counting 0/1, 1/1
