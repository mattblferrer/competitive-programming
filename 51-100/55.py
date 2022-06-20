# determines if the number given is a Lychrel number or not
def lychrel(num, limit):
    for i in range(limit):
        num = num + int(str(num)[::-1])
        if str(num) == str(num)[::-1]:
            return 0
    return 1


# given parameters
n = 10000
iterLimit = 50  # all non Lychrel numbers under n will reach a palindrome in less than this number of iterations
totalLychrel = 0

for i in range(n):
    if lychrel(i, iterLimit):
        print(i)
    totalLychrel += lychrel(i, iterLimit)

# final output
print("The total number of Lychrel numbers below", n, "is", totalLychrel)
