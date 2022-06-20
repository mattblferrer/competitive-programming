"""
For any given integer m and n, m > n > 0: 
a = m^2 - n^2
b = 2mn
c = m^2 + n^2,

is a valid Pythagorean triple
"""

sumABC = 1000  # given a+b+c = 1000
limit = 100  # loop iteration limit

for m in range(0,limit):
    for n in range(0,limit):
        # calculate a, b, c based on iterated values of m, n
        a = m**2 - n**2
        b = 2*m*n
        c = m**2 + n**2

        if a + b + c == 1000:
            ans = [a, b, c]  # store triple in array

print(ans)
print(ans[0]*ans[1]*ans[2])  # print product abc
