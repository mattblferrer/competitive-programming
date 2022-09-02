"""
This runs a bit slowly, and could be optimized. I included a running counter to
track its progress. 
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
            for j in [0, 2]:  # 6k+-1
                if n % (i + j) == 0:  # 
                    factors += 1
                    n //= (i + j)

                    if n % (i + j) == 0:
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
limit = 2**50
sqrtLimit = 2**25 + 1
squarefrees = 0

# main loop
for i in range(1, sqrtLimit):
    mob = mobius(i)
    squarefrees += mob*(limit // (i*i)) 

    # print working counter
    if i % 100000 == 0:
        print(i, squarefrees)

# print result
print("Number of squarefree numbers:", squarefrees)
