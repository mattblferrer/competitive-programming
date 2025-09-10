# declare variables
limit = 1000000  # maximum number of tiles

# count hollow laminae
laminae = 0

for m in range(3, int(limit**0.5)+1, 2):
    tiles = m*m - 1
    increment = (m-1)*2  # increment by this much every size increase

    # calculate number of laminae for each size of m
    laminae += (limit - tiles) // increment + 1

# print result
print(laminae)
