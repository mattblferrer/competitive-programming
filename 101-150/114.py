# returns the number of block combinations for a row of size r and block size b
def block_combs(b, r):
    if 0 <= r < b:
        return 1
    else:
        # count blocks recursively
        ways = blockList[r-1]

        for block_size in range(b, r+1):
            ways += blockList[r - block_size - 1]

        return ways


# declare variables
limit = 50
min_block = 3
blockList = [0]*(limit+2)  # number of block combinations for index r
# (This list starts at -1, so we add an index of 1 to everything)

# main loop
for i in range(limit+2):
    blockList[i] = block_combs(min_block, i)

# print result
print(blockList[limit+1])
