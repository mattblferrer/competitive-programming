from math import isqrt


sumABC = 1000  # given a+b+c = 1000
solutions = [0]*(sumABC+1)
maximumIndex = 0  # index where the number of solutions is maximized

# generating a, b, c
for a in range(1, sumABC//2):
    for b in range(1, sumABC//2):
        c2 = a*a + b*b
        c = isqrt(c2)
        if c*c == c2 and a+b+c <= sumABC:  # check for pythagorean triple
            solutions[a+b+c] += 1

# finding maximum value p
maximumIndex = solutions.index(max(solutions))

# final output
print(f"The value of p where the number of solutions is maximized is {maximumIndex}")
