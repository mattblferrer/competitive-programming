from math import prod


def main():
    def generate_factorizations(factors: list[int], limit: int) -> None:
        """generates all possible factorizations of n from 1 to limit - 1 and
        appends them to pre-created list"""
        highest = max(factors) if factors else 2
        product = prod(factors) if factors else 1
        if product < limit:
            factorizations[product].append(factors)

        for i in range(highest, limit // product + 1):
            generate_factorizations(factors + [i], limit)

        return None


    def drs(n: int) -> int:
        """returns the digital root sum of n"""
        return (n - 1) % 9 + 1


    def mdrs(n: int) -> int:
        """returns the maximum digital root sum of all the factorizations of
        n"""
        maximum = 0
        for factorization in factorizations[n]:
            drs_total = sum(drs_arr[i] for i in factorization)
            if drs_total > maximum:
                maximum = drs_total

        return maximum


    # declare variables
    limit = 1_000_000
    factorizations = [[] for _ in range(limit)]
    drs_arr = [drs(i) for i in range(limit)]
    sum_mdrs = 0

    # generate factorizations and calculate maximum digital root sum
    generate_factorizations([], limit)
    for i in range(1, limit):
        sum_mdrs += mdrs(i)

    # print result
    print(sum_mdrs)


if __name__ == "__main__":
    main()
