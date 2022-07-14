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
n = 0
min_block = 50
limit = 1000000
blockList = [0]  # number of block combinations for index r
# (This list starts at -1, so we add an index of 1 to everything)

# main loop
while True:
    blockList[n] = block_combs(min_block, n)

    if blockList[n] > limit:
        break

    n += 1
    blockList.append(0)

# print result
print("For m = 50, the least value of n =", n-1)