


def main():
    # returns the number of block combinations for a row of size r and 
    # block size b (no gaps, multiple block lengths b)
    def block_combs_ng(b: list[int], r: int) -> int:
        if 0 <= r < min(b):
            return 1
        # count blocks recursively
        ways = block_list[r-1]

        # check all possible block sizes in b
        for block_size in b:
            ways += block_list[r - block_size]

        return ways


    # declare variables
    block_list = [1, 1, 1, 1]
    b = [2, 3, 4]
    limit = 50

    # main loop
    for i in range(limit+2):
        block_list[i] = block_combs_ng(b, i)
        block_list.append(0)

    # print result
    print(block_list[50])


if __name__ == "__main__":
    main()
