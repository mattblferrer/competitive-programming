# declare variables
limit = 1000000  # maximum number of tiles

# count hollow laminae that used a certain number of tiles
Ln = [0]*(limit+1)
Nn = 0

for s in range(1, int(limit**0.5)+1):  # s = m-n (subtract)
    for p in range(s+1, int(limit//s)+1):  # p = m+n (plus)
        if (p+s) % 2 == 0:  # check if m is an integer
            m = (p+s) // 2
            n = p-m

            if (m-n) % 2 == 0:  # valid square lamina
                Ln[m*m - n*n] += 1

# count which t's have type L(n)
valid = list(range(1, 11))  # valid type values

for i in range(8, limit, 2):
    if Ln[i] in valid:
        Nn += 1

# print result
print(Nn)