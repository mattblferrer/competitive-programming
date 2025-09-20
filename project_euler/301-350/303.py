from math import log10
import numpy as np # type: ignore


def main():
    # declare variables
    limit = 10_000
    fn_sum = 2
    av = {i for i in range(3, limit + 1)}  # exclude 0, 1, 2 as solved 
    log = int(log10(limit))
    idx = 1

    # go through all ternary numbers until all n, f(n) / n is found
    while av:
        n = int(np.base_repr(idx, base=3))  # generate ternary representation
        length = len(av)  # numbers n, such that f(n) / n not calculated

        # special case for largest 10**k - 10 and (10**k - 10) / 2
        if length == 3:
            n = int("1" * (log - 1) + "2" * (4 * log - 4) + "0")

        # special case for largest 10**k - 1
        if length == 1:
            n = int("1" * log + "2" * (4 * log))

        # normal case
        div = [x for x in av if n % x == 0]
        if div:  # if there are multiples of n found, print
            print(f"index: {idx}, n: {n}, {length} numbers left")

        for x in div:  # for all pairs found, update f(n) / n
            av.remove(x)
            fn_sum += n // x
        
        idx += 1

    # print result
    print(f"sum: {fn_sum}")


if __name__ == "__main__":
    main()
