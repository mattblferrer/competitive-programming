def ABC115D() -> int:
    dp = {}

    def patties(n: int, x: int) -> int:
        if n == 1:  # base case BPPPB
            if x == 5:
                return 3
            if x == 0:
                return 0
            return x - 1
        if (n, x) in dp:  # cache to speed up
            return dp[(n, x)]

        smaller = burger_sizes[n - 1]  # layers in burger level n-1
        top_half = min(smaller, x - smaller - 2)  # not counting top B, middle P
        bottom_half = min(smaller, x - 1)  # not counting bottom B

        if x >= smaller + 2:  # B + smaller burger + P + top half
            p = (1 + patties(n - 1, bottom_half) + patties(n - 1, top_half))
        else:  # B + bottom half
            p = patties(n - 1, max(0, x - 1))
        dp[(n, x)] = p
        return p  

    # get number of layers for each burger level
    burger_sizes = [1]
    for _ in range(50):
        burger_sizes.append(2 * burger_sizes[-1] + 3)

    n, x = map(int, input().split())
    return patties(n, x)

print(ABC115D())