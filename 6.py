n = 100
sumOfSquares = 0

# sum of squares
for i in range(1, n+1):
    sumOfSquares += i**2

# square of sum
sumOfNums = n*(n+1)//2
squareOfSum = sumOfNums**2

diff = squareOfSum - sumOfSquares
print(diff)
