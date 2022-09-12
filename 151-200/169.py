# function that converts decimal to binary
def dec_to_bin(num: int) -> str:
    bin_str = bin(num).replace("0b","")
    return bin_str


# declare variables
n = 10**25

# get powers of two that add up to num (binary)
binN = reversed(dec_to_bin(n))  # reversed binary expansion of n
powersOf2 = [i for i, digit in enumerate(binN) if digit == '1']

# continuously split up 2^n into 2^(n-1)
fN = 0
# TODO

# print result
print(powersOf2)
