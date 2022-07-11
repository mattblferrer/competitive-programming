# declare variables
limit = 1000
rmaxSum = 0

# main loop
for a in range(3, limit+1):
    # (a-1)^n + (a+1)^n mod a^2 = 2*n*a mod a^2 for odd n
    # therefore, choose largest odd n such that 2*n*a < a*a
    # this happens when n = a-1, 2*n*a = 2*(a-1)//2*a = (a-1)*a
    n = (a-1) // 2
    r = (2*n*a) % (a*a)

    rmaxSum += r

# print results
print("The sum of rmax is equal to", rmaxSum)
