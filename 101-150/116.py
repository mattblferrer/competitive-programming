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
redList = [1, 1]
greenList = [1, 1, 1]
blueList = [1, 1, 1, 1]
# (These lists start at -1, so we add an index of 1 to everything) 
limit = 50

# main loop
for i in range(limit+2):
    redList[i] = block_combs_ng(2, i, redList)
    greenList[i] = block_combs_ng(3, i, greenList)
    blueList[i] = block_combs_ng(4, i, blueList)

    redList.append(0)
    greenList.append(0)
    blueList.append(0)

# calculate result, excluding the possibilities where 0 tiles are used
total = redList[limit+1] + greenList[limit+1] + blueList[limit+1] - 3

# print result
print(total)
