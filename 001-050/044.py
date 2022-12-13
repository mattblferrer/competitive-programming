# generates pentagonal number of certain index
def pentagonal(ind: int) -> int:
    return ind * (3 * ind - 1) // 2


# determines if number num is pentagonal
def is_pentagonal(num: int) -> bool:
    pent_check = ((24 * num + 1) ** 0.5 + 1) / 6
    return pent_check.is_integer()


# difference of pentagonal numbers p_j and p_k
def diff_pent(positions: list[tuple[int]]) -> tuple[int]:
    # calculate p_j - p_k
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

    # iterate from highest to lowest index to decrease difference
    for i in range(length-1, 0, -1):  
        if is_pentagonal(num + pent_list[i-1]):
            solutions.append((ind, i))

    return solutions


def main():
    # declare variables
    difference = 0  # difference between p_j and p_k
    index = 3  # starting index for pentagonal()
    pentagonal_list = [1, 5]  # list of pentagonal numbers calculated
    current_pentagonal = pentagonal(index)  # starting pentagonal

    # loop until p_j and p_k are found
    while difference == 0:
        # compute current pentagonal number
        pentagonal_list.append(current_pentagonal)

        # loop through pentagonal numbers until soln j and k, for which 
        # p_j + p_k is pentagonal is found
        pentagonal_sum = sum_pent(pentagonal_list, index)  

        if pentagonal_sum:
            pentagonal_diff = diff_pent(pentagonal_sum)
            if pentagonal_diff is not None:
                # get p_j, p_k, and difference values and print
                p_j, p_k, difference = pentagonal_diff
                print(f"p_k: {p_k}, p_j: {p_j}, Difference: {difference}")

        index += 1
        current_pentagonal += 3*index - 2  # generate next pentagonal number


if __name__ == "__main__":
    main()
