"""
The diagonals follow a formula:

1. Top right: (2n-1)^2 - 6(n-1)
2. Top left: (2n-1)^2 - 4(n-1)
3. Bottom left: (2n-1)^2 - 2(n-1)
4. Bottom right: (2n-1)^2

The bottom right diagonal always yields squares, and will not be useful for the program.
"""


# determines if num is prime
def isprime(num):
    if num == 2 or num == 3:  # for 2 and 3
        return True

    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(6, int(num**0.5)+3, 6):  # for 6k +- 1
        if num % (i-1) == 0:
            return False
        if num % (i+1) == 0:
            return False
    return True


# returns the next entry in the spiral diagonal
def next_spiral_diagonal(num):
    return (2*num-1)**2 - 6*(num-1), (2*num-1)**2 - 4*(num-1), (2*num-1)**2 - 2*(num-1)


# declare variables
n = 3  # starting n
numberOfPrimes = 3
totalDiagonals = 5  # total number of diagonal numbers, including 1

# main loop
while (numberOfPrimes / totalDiagonals) > 0.1:
    totalDiagonals += 4

    # create new spiral layer
    for number in next_spiral_diagonal(n):
        if isprime(number):
            numberOfPrimes += 1

    # increment
    n += 1

# print result
sideLength = (totalDiagonals - 1)//2 + 1  # remove 1, divide by 4, then get the side length
print("The side length of the square spiral for which the ratio of primes falls below 10% is", sideLength)
