from collections import defaultdict
from functools import cache
from itertools import product
from math import gcd, prod, isqrt


@cache
# returns the prime factors of num with multiplicity (repeating)
def prime_factorize(num: int) -> dict[int]:
    factors = {}

    for i in (2, 3):
        count = 0
        while num % i == 0:  # for only even prime
            count += 1
            num //= i
        if count:
            factors[i] = count

    for i in range(5, isqrt(num) + 1, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            count = 0
            while num % (i+j) == 0:
                count += 1
                num //= (i+j)
            if count:
                factors[i+j] = count

    if num != 1:
        factors[num] = 1

    return factors


# returns the Euler's totient of the number num using Euler's product formula
def totient(num: int, p_factors: list[int]) -> int:
    phi = num  # totient
    for factor in p_factors:
        phi = phi*(factor-1)//factor

    return phi


# returns the least common multiple of an array of numbers
def lcm_arr(arr: list[int]) -> int:
    lcm = 1
    for i in arr:
        lcm = lcm * i // gcd(lcm, i)
    return lcm


# divides out all factors of 2 and 5
def div_2_5(n: int) -> bool:
    for i in (2, 5):
        while n % i == 0:
            n //= i
            if n == 1:
                break

    return n


# returns the factors of num (non-repeating)
def factorize(num: int) -> list[int]:
    factor_ctr = prime_factorize(num)
    powers = [
        [base**power for power in range(count+1)]
        for base, count in factor_ctr.items()
    ]
    factors = [prod(power_combo) for power_combo in product(*powers)]

    return factors


# returns the Carmichael function or reduced totient function of num
def carmichael(num: int) -> int:
    factor_ctr = prime_factorize(num)

    # if prime power
    if len(factor_ctr) == 1:  
        for base, power in factor_ctr.items():
            if base == 2 and power > 2:
                return totient(num, list(factor_ctr)) // 2
            else:
                return totient(num, list(factor_ctr))

    # if not prime power
    l_lambdas = [carmichael(base**power) for base, power in factor_ctr.items()]
        
    return lcm_arr(l_lambdas)


# get length of recurring cycle of decimal fraction
def recurring_cycle(n: int) -> int:
    if n == 1:  # if terminates
        return 0

    for k in sorted(factorize(carmichael(n))):
        if pow(10, k, n) == 1:
            return k


# divides dividend by n
def long_division(dividend: int, n: int):
    dividend *= 10

    # continued long division, only have to check up to n digits
    for _ in range(n-1):  
        if dividend // n == 0:  # multiply dividend by 10 and move to the right
            dividend *= 10
            yield 0

        else:
            # long division step
            quotient, remainder = divmod(dividend, n)
            dividend = remainder * 10
            yield quotient


def main():        
    # declare variables
    left_digit_num = 11
    left_digits = 137
    right_digits = 56789

    # calculate possible range of numbers
    l_limit = (10**left_digit_num) // (left_digits + 1) + 1  # lower limit
    u_limit = (10**left_digit_num) // left_digits  # upper limit

    # get cyclic primes 
    arr = []  # stores cyclic prime denominators
    unique_freq = defaultdict(int)  # stores the frequency of denominators mod 100,000

    for n in range((l_limit // 2)*2 + 1, u_limit, 2):  # check odds only
        if unique_freq[n % 100_000]:  # check if mod is unique
            continue

        if not recurring_cycle(div_2_5(n)) == n-1:  # check if cyclic
            continue

        # check if rightmost digits match
        dec = 1 / n
        rc = right_digits / 100_000
        lc = dec * 1_000

        # get fractional part only
        frac_rem = ((rc + lc) / dec) - ((rc + lc) // dec)
        unique_freq[n % 100_000] += 1
        arr.append((frac_rem, n))
        print(f"n: {n}")

    # take sum of digits of decimal expansion
    n = list(reversed(sorted(arr)))[0][1]  # get n of best guess of cyclic
    sum_digits = 0        

    for i, digit in enumerate(long_division(1, n)):
        sum_digits += digit

        # get last 5 digits of cyclic number
        if i == n - 7: 
            last_5_digits = []

        elif i > n - 7:
            last_5_digits.append(digit)

        # check digits
        if i == n - 2 and last_5_digits == [5, 6, 7, 8, 9]:
            print(f"sum: {sum_digits}")

        if i % 100_000_000 == 0:  # progress tracker
            print(f"checking {n}, digit: {i}")


if __name__ == "__main__":
    main()
    