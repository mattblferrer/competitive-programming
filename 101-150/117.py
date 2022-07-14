# returns the number of block combinations for a row of size r and block size b
# (no gaps, multiple block lengths b)
def block_combs_ng(b, r):
    if 0 <= r < min(b):
        return 1
    else:
        # count blocks recursively
        ways = blockList[r-1]

        # check all possible block sizes in b
        for block_size in b:
            ways += blockList[r - block_size]

        return ways


# declare variables
blockList = [1, 1, 1, 1]
b = [2, 3, 4]
limit = 50

# main loop
for i in range(limit+2):
    blockList[i] = block_combs_ng(b, i)
    blockList.append(0)

# calculate result
total = blockList[50]

# print result
print(total)
