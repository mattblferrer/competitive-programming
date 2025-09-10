# determines if the number given is a Lychrel number or not
def lychrel(num, limit):
    for _ in range(limit):
        num = num + int(str(num)[::-1])
        if str(num) == str(num)[::-1]:
            return 0
    return 1


# given parameters
n = 10000
iterLimit = 50  # all non Lychrel numbers under n will reach a palindrome in less than this number of iterations
totalLychrel = sum(lychrel(i, iterLimit) for i in range(1, n))

# final output
print(f"The total number of Lychrel numbers below {n} is {totalLychrel}")
