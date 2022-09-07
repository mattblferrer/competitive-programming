# returns the number of block combinations for a row of size r and block size b
# (no gaps)
def block_combs_ng(b, r, blockList):
    if 0 <= r < b:
        return 1
    else:
        # count blocks recursively
        ways = blockList[r-1]
        for block_gap in range(b, r+1, b):
            ways += blockList[r - block_gap - 1]

        return ways


# declare variables
redList = [1]*2
greenList = [1]*3
blueList = [1]*4
# (These lists start at -1, so we add an index of 1 to everything)
colorList = [redList, greenList, blueList]
limit = 50

# main loop
for i in range(limit+2):
    for j, color in enumerate(colorList, start=2):
        color[i] = block_combs_ng(j, i, color)
        color.append(0)

# calculate result, excluding the possibilities where 0 tiles are used
total = sum(color[limit+1] - 1 for color in colorList)

# print result
print(total)
