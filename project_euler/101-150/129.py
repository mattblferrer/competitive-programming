"""
Looking at the sequence of A(n), A(n) is always less than n. Therefore, we can
start at n = 1,000,001 and check odd numbers for divisibility. 
"""


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
    limit = 1_000_000
    n = limit + 1
    a_n = 0

    # main loop
    while a_n < limit:
        n += 2
        if n % 5 == 0:
            n += 2

        a_n = repunit_a(n)

    # print result
    print("The least value of n is:", n)


if __name__ == "__main__":
    main()
