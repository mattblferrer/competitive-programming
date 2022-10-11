from math import isqrt


# returns the even indexed characters in string
def even_index(string: str) -> str:
    return string[::2]


# checks if the square satisfies the concealed square property
def concealed_check(string: str) -> bool:
    if string == "1234567890":
        return True
    return False


# declare variables
lower_limit = isqrt(1121314151617181900) // 330 * 330  # multiples of 330
upper_limit = isqrt(1929394959697989900) // 330 * 330

# main loop (check n^2)
for n in range(lower_limit, upper_limit, 330):
    sqr = str(n*n)

    # loop through all possible concealed numbers
    if concealed_check(even_index(sqr)):
        # print result
        print("The square is:", sqr)
        print("The number is:", n)
        break
