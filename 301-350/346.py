def main():
    # declare variables
    limit = 10**12
    repunit_set = {1}

    # loop through all bases b that can form a repunit below the limit
    for b in range(2, limit):
        k = b*b + b + 1  # start at 111 base b
        p = 3

        if k > limit:
            break

        while k < limit:
            repunit_set.add(k)
            k += b**p
            p += 1

    # print result
    print(sum(repunit_set))


if __name__ == "__main__":
    main()
