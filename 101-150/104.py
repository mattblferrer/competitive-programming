# checks if a number num is pandigital
def pandigital_check(num):
    digits_used = {int(digit) for digit in str(num)}

    if digits_used == set(range(1, 10)):
        return True
    return False


# declare variables
a, b = 1, 1  # starting Fibonacci numbers
ctr = 2  # Fibonacci index

# get first 16 digit Fibonacci numbers
while True:
    if a < 10**15:
        a, b = b, a+b

    else:
        # last 9 digits
        aL, bL = a % 10**9, b % 10**9

        # first 16 digits (for imprecision)
        aF, bF = a // 10, b // 10
        break

    ctr += 1

# main loop
while True:
    aL, bL = bL, (aL + bL) % (10**9)
    aF, bF = bF, aF + bF

    # check if first digits have more than 16 digits (precision wiggle room)
    if bF > 10**16:
        aF //= 10
        bF //= 10

    ctr += 1  # increment index

    # check first and last 9 digits
    if pandigital_check(bL) and pandigital_check(str(bF)[:9]):  
        # print results
        print("k: ", ctr)
        break
        