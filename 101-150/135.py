# declare variables
limit = 1000000
solutionNum = [0]*(limit)

# main loop
# the limit here is (5/4)*limit because 5^2 - 4^2 - 3^2 is an arithmetic
# progression that can be scaled up to get the maximum ratio possible to keep
# n between 0 and the limit
for x in range(1, int((5/4)*limit)):
    for y in range((4*x) // 5, x // 2, -1):
        # get difference of arithmetic progression
        diff = x - y
        z = y - diff

        # check solution
        soln = x*x - y*y - z*z
        if soln >= limit:
            break

        solutionNum[soln] += 1

# find values of n with 10 distinct solutions
answer = 0

for solns in solutionNum:
    if solns == 10:
        answer += 1

# print result
print("Number of values of n with 10 distinct solutions:", answer)
