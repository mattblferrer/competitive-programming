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
    for i in [2, 3]:  # for 2 and 3
        if n % i == 0:  
            n //= i
            if n % i == 0:  # if divisible again
                return False

    for i in range(5, int(n**0.5)+2, 6):  # for 6k +- 1
        for j in [0, 2]:
            if n % (i + j) == 0:
                n //= (i + j)
                if n % (i + j) == 0:
                    return False

    return True


# declare variables
rows = 50
currRow = [1]
numSet = set()

# generate Pascal's triangle rows
for i in range(rows):
    currRow = next_pascal_row(currRow)
    numSet = numSet.union(set(currRow))

# calculate squarefree sum
squarefreeSum = sum(i for i in numSet if is_squarefree(i))

# print result
print("Sum of distinct squarefree numbers:", squarefreeSum)
