# pre-computed list of all factorials 0-9
factorialList = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880]

# output variable
totalSum = 0

# iterate through numbers
for i in range(10, factorialList[9]*7):  # only have to check until 7*9!
    factorialSum = 0
    digits = [int(digit) for digit in str(i)]
    for digit in digits:
        factorialSum += factorialList[digit]
    if factorialSum == i:
        totalSum += i
        print(i)

# final output
print("The sum of all numbers which are equal to the factorial of their digits is", totalSum)
