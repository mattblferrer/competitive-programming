# generates pentagonal number of certain index
def pentagonal(ind):
    return ind*(3*ind-1)//2


# determines if number num is pentagonal
def is_pentagonal(num):
    pent_check = ((24*num+1)**0.5 + 1)/6
    if pent_check.is_integer():
        return True
    return False


# difference of pentagonal numbers Pj and Pk
def diff_pent(positions):
    # calculate Pj - Pk
    for item in positions:
        j = item[0]
        k = item[1]
        p_j = pentagonal(j)
        p_k = pentagonal(k)
        diff = p_j - p_k

        # if difference is pentagonal, return
        if is_pentagonal(diff):
            return p_j, p_k, diff


# sum of pentagonal number num and current pentagonal list
def sum_pent(pent_list, ind):
    num = pentagonal(ind)
    length = len(pent_list)
    solutions = []  # all possible solutions for index ind

    for i in range(length-1, 0, -1):  # iterate from highest to lowest index to decrease difference
        if is_pentagonal(num + pent_list[i-1]):
            solutions.append((ind, i))

    return solutions


# declare variables
difference = 0  # difference between Pj and Pk
index = 3  # starting index for pentagonal()
pentagonalList = [1, 5]  # list of pentagonal numbers calculated

# loop until Pj and Pk are found
while difference == 0:
    # compute current pentagonal number
    currentPentagonal = pentagonal(index)
    pentagonalList.append(currentPentagonal)

    # loop
    pentagonalSum = sum_pent(pentagonalList, index)  # j and k, for which Pj + Pk is pentagonal

    if pentagonalSum:
        pentagonalDiff = diff_pent(pentagonalSum)
        if pentagonalDiff is not None:
            # get Pj, Pk, and difference values
            Pk = pentagonalDiff[0]
            Pj = pentagonalDiff[1]
            difference = pentagonalDiff[2]

            print("Pk: {}, Pj: {}, Difference: {}".format(Pk, Pj, difference))
    index += 1
