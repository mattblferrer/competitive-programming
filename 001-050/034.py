# returns the sum of the factorials of the digits of num
def fac_digit_sum(num):
    factorial_list = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880]  # pre-computed list of all factorials 0-9
    factorial_sum = 0

    # take factorials of digits
    while num > 0:
        digit = num % 10
        factorial_sum += factorial_list[digit]
        num //= 10

    return factorial_sum


# output variable
totalSum = 0

# iterate through numbers
for i in range(10, 362880 * 7):  # only have to check until 7*9!
    if fac_digit_sum(i) == i:
        totalSum += i
        print(i)

# final output
print("The sum of all numbers which are equal to the factorial of their digits is", totalSum)
