from math import sqrt


# returns the even indexed characters in string
def even_index(string):
    output = ""
    for i in range(0, len(string), 2):
        output += string[i]

    return output


# checks if the square satisfies the concealed square property
def concealed_check(num):
    if num == "1234567890":
        return True
    return False


# declare variables
lowerLimit = (int(sqrt(1121314151617181900)) // 330) * 330
upperLimit = (int(sqrt(1929394959697989900)) // 330) * 330
n = lowerLimit

# main loop (check n^2)
while n < upperLimit:
    sqr = str(n*n)

    # loop through all possible concealed numbers
    if concealed_check(even_index(sqr)):
        # print result
        print("The square is:", sqr)
        print("The number is:", n)
        break

    n += 330
