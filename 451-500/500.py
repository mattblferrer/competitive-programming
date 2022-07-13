"""
Let a(n) be the smallest number with 2^n divisors. 
We can express a(n) as the product of n terms of the Fermi-Dirac primes:
numbers p^(2^k), for integer k and prime p. 

Source: https://oeis.org/A037992 
 """


from math import sqrt, log


# determines if num is a Fermi-Dirac prime
def is_fd_prime(num):
    power = 0

    if num % 2 == 0:  # for even numbers
        while num % 2 == 0:
            num //= 2
            power += 1

        # check if power of 2 or exponent != 2^k
        if num == 1 and (log(power, 2).is_integer() or power == 1):  
            return True
        return False

    else:
        for i in range(3, int(sqrt(num))+1, 2):  # for odd numbers
            if num % i == 0:
                while num % i == 0:
                    num //= i
                    power += 1

                # check if power of 2 or exponent != 2^k
                if num == 1 and (log(power, 2).is_integer() or power == 1):  
                    return True
                return False
            
        # if no factors below sqrt(n) divide n
        return True


# declare variables
limit = 500500
mod = 500500507
x = 1

# main loop
primes = 0
n = 2

while primes < limit:
    if is_fd_prime(n):
        primes += 1
        x *= n

        # calculate mod
        if x > mod:
            x = x % mod

    n += 1
    
# print result
print(x)
