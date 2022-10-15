from math import isqrt, sqrt


# returns the sums of the squares of the factors of num
def sum_factors_sqr(num: int) -> int:
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

    # calculate the sum of the squares of the factors of num
    sum_sf = 1
    for prime, power in factors.items():
        sum_sf *= (prime**(2*power + 2)-1) // (prime*prime - 1)

    return sum_sf


def main():
    # declare variables
    limit = 64_000_000
    sumN = 0

    # main loop
    for i in range(1, limit):
        if sqrt(sum_factors_sqr(i)).is_integer():  # check if perfect square
            sumN += i

        if i % 100000 == 0:  # progress tracker
            print(i, sumN)

    # print result
    print(f"Sum of all n: {sumN}")


if __name__ == "__main__":
    main()
