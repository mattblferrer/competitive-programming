"""
Looking at the sequence of A(n), A(n) is always less than n. Therefore, we can
start at n = 1,000,001 and check odd numbers for divisibility. 
"""


# returns a(n) for a given n
def repunit_a(n):
    r = 1  # start at R1
    a = 1  # 

    # check remainder, else check next repunit
    while r != 0:
        r = (r*10 + 1) % n
        a += 1
        
        if a > n:  # A(n) can never exceed n
            return n - 1

    return a


# declare variables
limit = 1000000
n = limit + 1

# main loop
while True:
    if n % 5 != 0:
        aN = repunit_a(n)

        if aN > limit:
            break

    n += 2

# print result
print("The least value of n is:", n)
