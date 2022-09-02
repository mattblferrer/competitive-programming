"""
1/x + 1/y = 1/n 
Solving for x and y, we get:
y/xy + x/xy = 1/n
x+y = xy/n
nx + ny = xy
nx - xy + ny = 0
(x-n)(y-n) = n^2

Therefore, the solutions of x and y have to satisfy (x-n)(y-n) = n^2.
x-n and y-n are factors of n^2

Therefore, the number of solutions increases as the number of factors increases.
n has to be a highly composite number for it to have the most factors. 
"""
from math import prod


# returns the number of solutions to Diophantine eqn 1/x + 1/y = 1/num for num 
def number_factors_sqr(num):  
    prime_factors = set()
    powers = []
    total_factors = 1

    while num % 2 == 0:  # check for even factors
        total_factors += 2
        num //= 2
        prime_factors.add(2)

    powers.append(total_factors - 1)

    # only have to check for odd factors up to limit
    # n^(1/4) is a guess limit on how fast primes in HCNs grow
    # (could be optimized)
    for i in range(3, int(num**0.25)+10, 2):  
        power = 1
        while num % i == 0:
            power += 2
            num //= i
            prime_factors.add(i)

        if power != 1:       
            powers.append(power - 1)

        total_factors *= power

    # get only positive solutions after x-num, return prime factors used
    return prime_factors, total_factors // 2 + 1, powers  


# declare variables
limit = 4000000
n = 4

# main loop
while True: 
    solved = number_factors_sqr(n)
    prime_fac = solved[0]  # prime factors used 
    solutions = solved[1]  # number of solutions

    if solutions > limit:
        break

    # increment n by product of prime factors
    product = prod(prime_fac)
    n += product

# backtrack to find real solution
product //= max(prime_fac)
iterlimit = n // 2  # there is always an HCN between n and 2n if we missed one
answer = n
ansSolutions = solutions

while n > iterlimit:
    n -= product

    solved = number_factors_sqr(n)
    prime_fac = solved[0]  # prime factors used 
    solutions = solved[1]  # number of solutions

    if solutions > limit:
        answer = n
        ansSolutions = solutions

# print result
print("The least value of n is", answer)
print("Number of solutions:", ansSolutions)
