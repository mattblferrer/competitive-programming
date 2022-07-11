# returns True if a number num is bouncy, and False otherwise
def is_bouncy(num):
    # number can't be bouncy below 100
    if num < 100:
        return False

    else:  
        digits = [int(digit) for digit in str(num)]

        # check if number is supposed to be increasing or decreasing
        if digits[0] < digits[-1]:
            is_increasing = True
        else:
            is_increasing = False 

        # calculate differences between adjacent digits
        diff_array = []
        for i, digit in enumerate(digits[1:]):
            diff_array.append(digit - digits[i])  # digit ahead - digit behind

        # check if number is bouncy based on differences
        for diff in diff_array:
            if diff > 0 and not is_increasing:
                return True
            elif diff < 0 and is_increasing:
                return True

        return False


# declare variables
bouncyNum = 0
n = 99
index = 1

# main loop
while True:
    if is_bouncy(n):
        bouncyNum += 1

    if bouncyNum / n == 0.99:  # check ratio
        # print result
        print("The least number for which the proportion is 99%\ is", n)
        break

    n += 1
