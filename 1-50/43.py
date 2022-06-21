from itertools import permutations


# checks for substring divisibility in the number
def subs_divisibility(num):
    digits = [int(d) for d in str(num)]  # get digits of num
    divisors = [2, 3, 5, 7, 11, 13, 17]

    for i in range(7):
        substring = digits[i+1]*100 + digits[i+2]*10 + digits[i+3]
        if substring % divisors[i] != 0:
            return False

    return True


# generate list of pandigital numbers
allDigits = "0123456789"
pandigitalList = [int(''.join(digits)) for digits in list(permutations(allDigits)) if digits[0] != '0']

# declare variables
pandigitalSum = 0

# iterate through all pandigital numbers in list
for n in pandigitalList:
    if subs_divisibility(n):
        pandigitalSum += n

print("The sum of all 0 to 9 pandigital numbers with this property is {}".format(pandigitalSum))
