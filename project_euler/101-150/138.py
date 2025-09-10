"""
Fibonacci(6*n + 3) / 2 gives L for n = 1, 2, 3 ...
Source: https://oeis.org/A007805
"""


# returns the nth fibonacci number
def fibonacci(n):
    ctr = 1
    a, b = 0, 1

    while ctr < n:
        a, b = b, a+b
        ctr += 1

    return b


# declare variables
triangles = 12

# calculate sum of L's of triangles
sumL = sum(fibonacci(6*i + 3) // 2 for i in range(1, triangles+1))

# print result
print("The sum of L is", sumL)
