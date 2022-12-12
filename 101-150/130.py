"""
Looking at the sequence of A(n), A(n) is always less than n. Therefore, we can
start at n = 1,000,001 and check odd numbers for divisibility. 
"""
# determines if num is prime
def isprime(num: int) -> bool:
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# returns a(n) for a given n
def repunit_a(n: int) -> int:
    a, r = 1, 1 # start at R1

    # check remainder, else check next repunit
    while r != 0:
        r = (r * 10 + 1) % n
        a += 1
        
        if a > n:  # A(n) can never exceed n
            return n - 1

    return a


def main():
    # declare variables
    composite_sum = 0
    n = 89  # given in the problem - 2  (2 will be added at start of loop)
    ctr = 0
    limit = 25

    # main loop
    while ctr < limit: 
        n += 2
        if n % 5 == 0 or isprime(n):
            continue
        
        a_n = repunit_a(n)
        if (n - 1) % a_n == 0:  # divisibility check
            ctr += 1
            composite_sum += n
        
    # print result
    print("The sum of the first 25 composite values of n is:", composite_sum)


if __name__ == "__main__":
    main()
