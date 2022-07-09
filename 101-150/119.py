from math import log, sqrt


# returns the sum of the digits of num
def digit_sum(num):
    return sum([int(digit) for digit in str(num)])


# return next perfect power
def next_power(num):
    possible_powers = set()
    high_exp = int(log(num, 2))+1  # highest exponent for next power

    # only have to check 2, odd exponents
    base = int(sqrt(num))+1
    power = base*base
    
    if power > num:
        possible_powers.add(power)

    # odd exponents
    for exponent in range(3, high_exp, 2):
        base = int(num ** (1/exponent))+1  # next base up
        power = base**exponent

        if power > num:
            possible_powers.add(power)

    return min(possible_powers)


# checks if num is a perfect power of a base
def is_power(num, base):
    high_exp = int(log(num, base))+2 # highest exponent for next power

    for exponent in range(high_exp - 2, high_exp):
        if base**exponent == num:
            return True

    return False


# declare variables
index = 1
n = 10  # initial value of power

# main loop
while True:
    n = next_power(n)
    digitSum = digit_sum(n)

    if digitSum > 1:
        if is_power(n, digit_sum(n)):
            print(index, n)
            index += 1
    
