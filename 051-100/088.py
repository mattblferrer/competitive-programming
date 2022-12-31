from itertools import combinations


def prime_factorize(num: int) -> list[int]:
    """returns the prime factors of num with multiplicity (repeating) as list"""
    factors = []

    for i in (2, 3):
        count = 0
        while num % i == 0:  # for only even prime
            count += 1
            num //= i
            factors.append(i)

    for i in range(5, int(num ** 0.5) + 1, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):
            count = 0
            while num % (i+j) == 0:
                count += 1
                num //= (i+j)
                factors.append(i+j)

    if num != 1:
        factors.append(num)

    return factors


def generate_factorizations(factors: tuple[int]) -> set[tuple[int]]:
    """generates all possible factorizations given the prime factors of n"""
    factorizations = {factors}
    if len(factors) == 1:  # factors = 1 * n
        [factor] = factors
        return {(factor, 1)}  # add 1 to single element factor set

    # recursively generate all factorizations from combining two factors
    for f_1, f_2 in set(combinations(factors, 2)):
        new_factors = list(factors)
        new_factors.remove(f_1)
        new_factors.remove(f_2)
        new_factors.append(f_1 * f_2)
        new_factors = tuple(sorted(new_factors))
        factorizations.update(generate_factorizations(new_factors))

    return factorizations


def main():
    # declare variables
    limit = 12_000
    product_sum = [0] * (limit + 1)
    product_sum[2] = 4

    # loop factorizations to find least product-sum for each chain length
    for i in range(2, 2 * limit + 1):
        prime_factors = prime_factorize(i)
        factorizations = generate_factorizations(tuple(prime_factors))
        
        for f in factorizations:
            f_sum = sum(f)
            f_length = len(f)

            if f_sum < i:   # product chain only possible if sum < n
                chain_length = i - f_sum + f_length
                if chain_length > limit:  # can't be product-sum number
                    continue

                if product_sum[chain_length] < f_sum:
                    product_sum[chain_length] = i

    # print unique product-sum numbers
    print(sum(set(product_sum)))


if __name__ == "__main__":
    main()
