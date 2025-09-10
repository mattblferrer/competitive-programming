"""
These functions generate the figurate or polygonal numbers from P3 to P8
"""


# generate triangular number of certain index
def triangular(ind: int) -> int:
    return ind * (ind + 1) // 2


# generate square number of certain index
def square(ind: int) -> int:
    return ind * ind


# generate pentagonal number of certain index
def pentagonal(ind: int) -> int:
    return ind * (3 * ind - 1) // 2


# generate hexagonal number of certain index
def hexagonal(ind: int) -> int:
    return ind * (2 * ind - 1)


# generate heptagonal number of certain index
def heptagonal(ind: int) -> int:
    return ind * (5 * ind - 3) //2


# generate octagonal number of certain index
def octagonal(ind: int) -> int:
    return ind * (3 * ind - 2)


# selects figurate number to calculate based on key
def calc_figurate(key: int, ind: int) -> int:
    figurates = {
        3: triangular,
        4: square,
        5: pentagonal, 
        6: hexagonal, 
        7: heptagonal, 
        8: octagonal
    }
    return figurates.get(key)(ind)


# find ordered set of cyclic numbers
def ord_set_cyclic(figurate_nums: list) -> list:
    def backtrack() -> tuple:
        c, p = num_index[-1] + 1, num_index[-2]

        current_cycle.pop(-1)
        num_index.pop(-1)
        keys_used.pop(-1)

        return c, p

    for s, figurate_num in enumerate(figurate_nums):
        current_cycle = [figurate_num]
        keys_used = [figurate_nums[s][0]]

        num_index = [s]  # indices of processed numbers
        c, p = s, s  # current, previous index

        while len(current_cycle) < 6:
            while c < len(figurate_nums):
                # check for first and last two digits and if keys are different
                if (figurate_nums[c][1] // 100 == figurate_nums[p][1] % 100) \
                    and (figurate_nums[c][0] not in keys_used):
                    current_cycle.append(figurate_nums[c])
                    num_index.append(c)
                    keys_used.append(figurate_nums[c][0])

                    # move forward in cycle
                    c, p = 0, num_index[-1]

                c += 1  # increment if check does not work

                # check if last two digits of 6th num = first two digits of 1st 
                # num (cycle)
                if len(current_cycle) == 6:
                    if current_cycle[5][1] % 100 == current_cycle[0][1] // 100:
                        return current_cycle
                    c, p = backtrack()

            # if no new element of cycle found, backtrack
            if not 1 < len(current_cycle) < 6:  
                break
            c, p = backtrack()


def main():
    # calculate list of figurate numbers between lower and upper limits
    lower_limit, upper_limit = 1000, 10000
    figurate_nums = []

    for key in range(3, 9):
        num, index = 0, 0

        while num < upper_limit:
            num = calc_figurate(key, index)

            if lower_limit < num < upper_limit:
                figurate_nums.append((key, num))

            index += 1

    # calculate sum of ordered set of cyclic numbers
    cycle = ord_set_cyclic(figurate_nums)  # cycle found
    cyclic_sum = sum(num[1] for num in cycle)

    # print result
    print(f"The sum of the ordered set of cyclic numbers is {cyclic_sum}")
    print(f"Set found: {cycle}")


if __name__ == "__main__":
    main()
