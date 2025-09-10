def main(): 
    # returns the number of block combinations for a row of size r and 
    # block size b
    def block_combs(b: int, r: int) -> int:
        if 0 <= r < b:
            return 1
        # count blocks recursively
        ways = block_list[r-1]

        for block_size in range(b, r+1):
            ways += block_list[r - block_size - 1]

        return ways


    # declare variables
    n = 0
    min_block = 50
    limit = 1_000_000
    block_list = [0]  # number of block combinations for index r
    # (This list starts at -1, so we add an index of 1 to everything)

    # main loop
    while True:
        block_list[n] = block_combs(min_block, n)

        if block_list[n] > limit:
            break

        n += 1
        block_list.append(0)

    # print result
    print("For m = 50, the least value of n =", n-1)


if __name__ == "__main__":
    main()
