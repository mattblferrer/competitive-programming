# calculates S(n) as a sum of r(k), k from 1 to n
def sn_235(n: int, r: int) -> int:
    sn = 0
    for k in range(1, n + 1):
        sn += (900 - 3*k)*r**(k-1)  # calculate u(k) for every k

    return sn


# declare variables
r = 0  # starting point
step = 0.1
sn_limit = -600_000_000_000
sn_arg = 5000
sn = sn_235(sn_arg, r)  # starting value of S(n)

# get limit from the left of r for S(5000) = -600,000,000,000
while step > 10**-13:  # precision given in problem + 1 decimal point
    while True:  
        sn = sn_235(sn_arg, r)

        if sn < sn_limit: 
            # if S(n) is greater, backtrack to highest r, S(n) is lower
            sn = sn_235(sn_arg, r-step)
            r -= step
            break

        r += step

    step /= 10  # narrow down step length as approximation of r gets closer

# print result
print(f"r for which S({sn_arg}) = {sn_limit}: {round(r, 12)}")
