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


    # declare variables
    limit = 12_000
    factorizations = [[] for _ in range(2 * limit + 1)]
    generate_factorizations([], 2 * limit + 1)
    product_sum = [0] * (limit + 1)
    product_sum[2] = 4

    # loop factorizations to find least product-sum for each chain length
    for i in range(2, 2 * limit + 1):
        for f in factorizations[i]:
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
