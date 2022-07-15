# generates the next convergent a/b of the square root of 2 over 2
def sqrt_two_convergent(a, b):
    return a+b, 2*a+b

# declare starting variables for a/b
a = 3
b = 4
limit = 10**12
mult = 1
ctr = 0

# main loop
while mult*b < limit:
    mult = b // 2  # multiplier to the fraction convergent
    a, b = sqrt_two_convergent(a, b)
    ctr += 1

# print result
if ctr % 2 == 1:  # check for even parity, then approximation is smaller of pair
        print(mult*a + 1, mult*b + 1)
else:
    print(mult*a, mult*b)  # approximation is bigger of pair for odd parity
