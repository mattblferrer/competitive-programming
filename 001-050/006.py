n = 100

# calculate sums
sumOfSquares = (n*(n+1)*(2*n+1)) // 6  # sum of squares
squareOfSum = n*n*(n+1)*(n+1) // 4  # square of sum

# print result
diff = squareOfSum - sumOfSquares
print(diff)
