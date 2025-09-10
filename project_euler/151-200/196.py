"""
CODE FOR PRINTING TRIANGLE:
for x in range(1, 25):
    i = 0
    while i < x:
        print(triangular(x) - x + i + 1, end=' ')
        i += 1
    print("")
"""
from functools import cache


# test for composite
def _try_composite(a: int, d: int, n: int, s: int) -> bool:
    if pow(a, d, n) == 1:
        return False
    for i in range(s):
        if pow(a, 2**i * d, n) == n-1:
            return False
    return True  # n  is definitely composite
 

@cache
# Miller-Rabin primality test
def is_prime_mr(n: int) -> bool:
    if n in _known_primes:
        return True
    if any((n % p) == 0 for p in _known_primes) or n in (0, 1):
        return False
    d, s = n - 1, 0
    while not d % 2:
        d, s = d >> 1, s + 1
    # Returns exact according to http://primes.utm.edu/prove/prove2_3.html
    if n < 1373653: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3))
    if n < 25326001: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5))
    if n < 118670087467: 
        if n == 3215031751: 
            return False
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7))
    if n < 2152302898747: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11))
    if n < 3474749660383: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13))
    if n < 341550071728321: 
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17))
    else:
        return not any(_try_composite(a, d, n, s) for a in (2, 3, 5, 7, 11, 13, 17, 19, 23))

_known_primes = [2, 3]


@cache
# generate triangular number of certain index
def triangular(ind: int) -> int:
    return ind*(ind+1)//2


# returns True if number is part of a prime triplet, False otherwise
def is_prime_triplet_196(num: int, row: int, t: int) -> bool:
    def generate_check(num: int, row: int, t: int) -> list[int]:
        # if i is prime
        parity_2 = row % 2  # tells which neighbors are odd (prime candidates)
        if not parity_2:  # 2 above, 1 below
            check = [num-row, num-row+2, num+row]

        else:  # 1 above, 2 below
            check = [num-row+1, num+row-1, num+row+1]
            
        # check if check numbers are valid
        for i in check:
            # if overflowed from previous row from left
            if num == 1+t and i == triangular(row): 
                check.remove(i)

        return check


    if not is_prime_mr(num):
        return False

    # check if number i is part of a triplet (prime check)
    check = generate_check(num, row, t)
    prime_number = sum(is_prime_mr(i) for i in check)

    if prime_number > 1:  # i is the middle of a triplet
        return True
    elif prime_number == 1:  # check if i is on the edge of triplet
        # iterate through all neighbors and check if they are middle of triplet
        for i in check:  
            if is_prime_mr(i):
                if i < num-row+3:  # if i above num
                    check_2 = generate_check(i, row-1, triangular(row-1))
                else:  # if i below num
                    check_2 = generate_check(i, row+1, triangular(row+1))

                prime_number = sum(is_prime_mr(j) for j in check_2)
                if prime_number > 1:
                    return True
                
    return False


# declare variables
n_list = [5678027, 7208785]
t_list = [triangular(i-1) for i in n_list]  # start of row numbers - 1
s = 0  # S(n)

# loop through numbers in row n
for n, t in zip(n_list, t_list):
    parity = ((n // 2) - 1) % 2  # check parity of starting number in row
    j = 0
    for i in range(t+parity, t+n, 2):
        if j % 100000 == 0:  # progress tracker
            print(j)
        if is_prime_triplet_196(i, n, t):
            s += i
        j += 2

# print result
print(f"S(n): {s}")
