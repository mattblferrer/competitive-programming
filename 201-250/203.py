# generates next row of Pascal's triangle from the previous row
def next_pascal_row(row):
    output = [1]

    # calculate sums of previous row elements
    for i, n in enumerate(row[:len(row)-1]):
        output.append(n + row[i+1])

    output.append(1)

    return output


# returns True if the number n is squarefree, False otherwise
def is_squarefree(n):
    if n % 2 == 0:  # for 2
        n //= 2
        if n % 2 == 0:  # if divisible again
            return False

    if n % 3 == 0:  # for 3
        n //= 3
        if n % 3 == 0:  # if divisible again
            return False

    for i in range(5, int(n**0.5)+2, 6):  # for 6k +- 1
        if n % i == 0:
            n //= i
            if n % i == 0:
                return False

        if n % (i+2) == 0:
            n //= (i+2)
            if n % (i+2) == 0:
                return False

    return True


# declare variables
rows = 50
currRow = [1]
numSet = set()
squarefreeSum = 0

# generate Pascal's triangle rows
for i in range(rows):
    currRow = next_pascal_row(currRow)
    numSet = numSet.union(set(currRow))

# calculate squarefree sum
for i in numSet:
    if is_squarefree(i):
        squarefreeSum += i

# print result
print("Sum of distinct squarefree numbers:", squarefreeSum)
