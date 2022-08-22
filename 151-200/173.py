# declare variables
limit = 1000000  # maximum number of tiles

# count hollow laminae
laminae = 0

for s in range(1, int(limit**0.5)+1):  # s = m-n (subtract)
    for p in range(s+1, int(limit//s)+1):  # p = m+n (plus)
        if (p+s) % 2 == 0:  # check if m is an integer
            m = (p+s) // 2
            n = p-m

            if (m-n) % 2 == 0:  # valid square lamina
                laminae += 1

# print result
print(laminae)
