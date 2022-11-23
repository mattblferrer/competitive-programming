def main():
    # declare variables
    L = str(123)  # represent as string for faster comparisons
    n = 678910
    x, ctr, power, i_limit = 1, 1, 0, 20
    length = len(L)
    i_limit_power = 10**i_limit

    # find first 2^j (p(L, 1))
    while str(x)[:length] != L:
        x <<= 1
        power += 1

        if x > i_limit_power:  # guess limit, could be increased for accuracy 
            x //= 10

    # find subsequent 2^j (p(L, k), k < n)
    while ctr < n:
        x <<= 196
        if str(x)[:length] == L:  # gap between 2^j's = 196
            power += 196
        else:
            x <<= 93  # 289 - 196 = 93
            if str(x)[:length] == L:   # gap between 2^j's = 289
                power += 289
            else:   # gap between 2^j's = 485
                x <<= 196
                power += 485

        ctr += 1
        x = int(str(x)[:i_limit])

    # print result
    print(f"p({L}, {n}): {power}")


if __name__ == "__main__":
    main()
