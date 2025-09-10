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
    limit = 50
    min_block = 3
    block_list = [0]*(limit+2)  # number of block combinations for index r
    # (This list starts at -1, so we add an index of 1 to everything)

    # main loop
    for i in range(limit+2):
        block_list[i] = block_combs(min_block, i)

    # print result
    print(block_list[limit+1])


if __name__ == "__main__":
    main()
