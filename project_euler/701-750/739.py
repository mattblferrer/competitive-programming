from itertools import accumulate


def lucas_generator(limit: int, mod: int) -> int:
    """returns the Lucas sequence as a generator"""
    a, b = 2, 1
    ctr = 0

    while ctr < limit:
        a, b = b, (a + b) % mod
        yield a
        ctr += 1


def main():
    # TODO find faster way for partial summation
    # declare variables
    mod = 1_000_000_007
    length = 20
    lucas_numbers = [i for i in lucas_generator(length, mod)]

    # calculate cumulative sum for each iteration
    while length > 1:
        print(lucas_numbers)
        lucas_numbers.pop(0)
        lucas_numbers = [i % mod for i in accumulate(lucas_numbers)]
        length -= 1

    # print result
    print(lucas_numbers)


if __name__ == "__main__":
    main()
