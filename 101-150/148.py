"""
This program calculates the number of numbers not divisible by 7 in every row
up to the greatest a*7^b less than 10^9, a < 7.
Then, it calculates the remaining rows by brute force.
"""


# generate triangular number of certain index
def triangular(ind):
    return ind*(ind+1)//2


# converts number to base b
def num_to_base(num, b):
    while num > 0:
        num, d = divmod(num, b)
        yield d


# adds 1 to base b array
def base_add_one(num_arr, b):
    num_arr[0] += 1

    for i in range(len(num_arr)):
        if num_arr[i] >= b:
            num_arr[i] = 0
            num_arr[i+1] += 1
        
        else:
            return num_arr


# declare variables
limit = 10**9
row = 7

limit_conversion = list(num_to_base(limit, row))  # convert to base 7
highestPower = len(limit_conversion) - 1

totalNums = triangular(limit)
divisible = 0

# populate triangular count array
count = 0  # running count
triangularCount = [0]  # number of divisible nums for each fractal level

for i in range(1, highestPower):
    count += triangular(6) * triangular(7 ** i - 1)  # biggest triangles
    count += (triangular(7) - 1) * triangularCount[i - 1]  # smaller triangles
    triangularCount.append(count)

# calculate divisible with whole triangles
n = limit_conversion[-1]

divisible += triangular(n) * triangularCount[-1]  # smaller triangles
divisible += triangular(n-1) * triangular(7 ** (highestPower) - 1)

# calculate divisible with leftover partial triangles (brute force)
row = n * 7 ** highestPower
conv = list(num_to_base(row, 7))  # base 7 conversion of row number

for i in range(row+1, limit+1):
    divRow = 1  # number of divisible numbers in row

    for j in conv:  # calculate divisible nums 
        divRow *= j+1
        
    divisible += i - divRow
    conv = base_add_one(conv, 7)

# print result
notDivisible = totalNums - divisible
print("Rows not divisible by 7:", notDivisible)
