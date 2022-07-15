# returns the sum of the factorials of the digits of num
def fac_digit_sum(num):
    factorial_list = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880]  # pre-computed list of all factorials 0-9
    factorial_sum = 0

    digits = [int(digit) for digit in str(num)]

    # take factorials of digits
    for digit in digits:
        factorial_sum += factorial_list[digit]

    return factorial_sum


# returns the length of the factorial sum chain of num
def fac_digit_chain(num):
    current_chain = []
    counter = 0
    current_sum = num

    while current_sum not in current_chain:
        current_chain.append(current_sum)
        current_sum = fac_digit_sum(current_sum)
        counter += 1

    return counter


# declare variables
limit = 1000000
chainLength = [0]*1000000
answer = 0

# main loop
for i in range(limit):
    if fac_digit_chain(i) == 60:
        answer += 1

# print result
print("The number of chains that have 60 non-repeating terms:", answer)





