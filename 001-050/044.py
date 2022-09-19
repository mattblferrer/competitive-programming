# generates pentagonal number of certain index
def pentagonal(ind: int) -> int:
    return ind*(3*ind-1)//2


# determines if number num is pentagonal
def is_pentagonal(num: int) -> bool:
    pent_check = ((24*num+1)**0.5 + 1)/6
    if pent_check.is_integer():
        return True
    return False


# difference of pentagonal numbers Pj and Pk
def diff_pent(positions: list[tuple[int]]) -> tuple[int]:
    # calculate Pj - Pk
    for item in positions:
        (j, k) = item
        p_j = pentagonal(j)
        p_k = pentagonal(k)
        diff = p_j - p_k

        # if difference is pentagonal, return
        if is_pentagonal(diff):
            return p_j, p_k, diff


# sum of pentagonal number num and current pentagonal list
def sum_pent(pent_list: list[int], ind: int) -> list[tuple[int]]:
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
currentPentagonal = pentagonal(index)  # starting pentagonal

# loop until Pj and Pk are found
while difference == 0:
    # compute current pentagonal number
    pentagonalList.append(currentPentagonal)

    # loop through pentagonal numbers until soln found
    pentagonalSum = sum_pent(pentagonalList, index)  # j and k, for which Pj + Pk is pentagonal

    if pentagonalSum:
        pentagonalDiff = diff_pent(pentagonalSum)
        if pentagonalDiff is not None:
            # get Pj, Pk, and difference values and print
            Pj, Pk, difference = pentagonalDiff
            print(f"Pk: {Pk}, Pj: {Pj}, Difference: {difference}")

    index += 1
    currentPentagonal += 3*index - 2  # generate next pentagonal number
