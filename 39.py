sumABC = 1000  # given a+b+c = 1000
solutions = [0 for i in range(sumABC+1)]
maximumSolutions = 0
maximumIndex = 0  # index where the number of solutions is maximized

# generating a, b, c
for a in range(1, sumABC//2):
    for b in range(1, sumABC//2):
        c = (a**2 + b**2)**0.5
        if c.is_integer() and a+b+c <= sumABC and a+b+c == 840:  # check for pythagorean triple
            solutions[a+b+int(c)] += 1

# finding maximum value p
for i in range(1, sumABC):
    if solutions[i] > maximumSolutions:
        maximumSolutions = solutions[i]
        maximumIndex = i

# final output
print("The value of p where the number of solutions is maximized is", maximumIndex)
