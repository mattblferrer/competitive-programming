def main(): 
    # returns the number of block combinations for a row of size r and 
    # block size b (no gaps)
    def block_combs_ng(b: list[int], r: int, block_list: list[int]) -> int:
        if 0 <= r < b:
            return 1
        # count blocks recursively
        ways = block_list[r-1]
        for block_gap in range(b, r+1, b):
            ways += block_list[r - block_gap - 1]

        return ways


    # declare variables
    red_list = [1]*2
    green_list = [1]*3
    blue_list = [1]*4
    # (These lists start at -1, so we add an index of 1 to everything)
    color_list = [red_list, green_list, blue_list]
    limit = 50

    # main loop
    for i in range(limit+2):
        for j, color in enumerate(color_list, start=2):
            color[i] = block_combs_ng(j, i, color)
            color.append(0)

    # calculate result, excluding the possibilities where 0 tiles are used
    total = sum(color[limit+1] - 1 for color in color_list)

    # print result
    print(total)


if __name__ == "__main__":
    main()
