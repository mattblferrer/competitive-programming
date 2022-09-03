# function that converts decimal to binary
def dec_to_bin(num):
    bin_str = bin(num).replace("0b","")
    return bin_str


# declare variables
n = 10**25

# get powers of two that add up to num (binary)
binN = dec_to_bin(n)
i = 1  # starting power of 2
powersOf2 = []

for digit in reversed(str(dec_to_bin(n))):
    if digit == '1':
        powersOf2.append(i)
    i *= 2

# continuously split up 2^n into 2^(n-1)
fN = 0
# TODO

# print result
print(fN)
