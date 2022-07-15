# generate triangular number of certain index
def triangular(ind):
    return ind*(ind+1)//2


# determines if number num is pentagonal
def is_pentagonal(num):
    pent_check = ((24*num+1)**0.5 + 1)/6
    if pent_check.is_integer():
        return True
    return False


# determines if number num is hexagonal
def is_hexagonal(num):
    hex_check = ((8*num+1)**0.5 + 1)/4
    if hex_check.is_integer():
        return True
    return False


# given variables
index = 286

# loop until triangle, pentagonal, hexagonal number found
while True:
    triangle_num = triangular(index)  # triangular number to test
    if is_pentagonal(triangle_num) and is_hexagonal(triangle_num):
        break
    index += 1

# print final result
print("The next triangle number that is also pentagonal and hexagonal is", triangle_num)
