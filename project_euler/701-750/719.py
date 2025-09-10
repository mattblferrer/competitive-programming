"""
All S-numbers are congruent to 0 or 1 mod 9.
"""
from math import sqrt


# checks if a square number is an S number
def is_s_number(sqr: int, index: int) -> bool:
    # declare variables
    string = str(sqr)
    length = len(string) - 1
    index_length = len(str(index))
    formatting = f"0{length}b"  # to format to binary

    # there should be one split at least halfway through the number
    for subset_index in range(2**(index_length - 1) - 1, 2**length):
        if subset_index.bit_count() > index_length:  # > split limit
            continue
        subset_b = format(subset_index, formatting)

        # get subset of index subset_b and add terms
        split_index = [0] + [i for i, d in enumerate(subset_b, start=1) 
            if d == '1'] + [length + 1]

        # split number according to split subset
        split = [int(string[i:j]) for i, j in zip(split_index, split_index[1:])]
        n_sum = sum(split)

        # splitting number check
        if n_sum == index:
            print(index, string, split, subset_index, index_length, subset_b)
            return True
    
    return False


def main():
    # declare variables
    limit = 10**12
    sqr_limit = int(sqrt(limit))
    sqr, index = 1, 1  # square and its square root (index)
    s_sum = 0  # sum of all S numbers (T(N))

    # main loop
    while index <= sqr_limit:
        if is_s_number(sqr := sqr + 16*index + 64, index := index + 8):  # 0
            s_sum += sqr

        if is_s_number(sqr := sqr + 2*index + 1, index := index + 1):  # 1
            s_sum += sqr

    # print result
    print(f"T({limit}) = {s_sum}")


if __name__ == "__main__":
    main()
