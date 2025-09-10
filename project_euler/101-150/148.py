"""
This program calculates the number of numbers not divisible by 7 in every row
up to the greatest a*7^b less than 10^9, a < 7.
Then, it calculates the remaining rows by brute force.
"""


def triangular(ind: int) -> int:
    """generate triangular number of certain index"""
    return ind * (ind + 1) // 2


def num_to_base(num: int, b: int) -> int:
    """converts number to base b"""
    while num > 0:
        num, d = divmod(num, b)
        yield d



def base_add_one(num_arr: list[int], b: int) -> list[int]:
    """adds 1 to base b array"""
    num_arr[0] += 1

    for i in range(len(num_arr)):
        if num_arr[i] >= b:
            num_arr[i] = 0
            num_arr[i+1] += 1
        
        else:
            return num_arr


def main():
    # declare variables
    limit = 10**9
    row = 7

    limit_conversion = list(num_to_base(limit, row))  # convert to base 7
    highest_power = len(limit_conversion) - 1

    total_nums = triangular(limit)
    divisible = 0

    # populate triangular count array
    count = 0  # running count
    triangular_count = [0]  # number of divisible nums for each fractal level

    for i in range(1, highest_power):
        count += triangular(6) * triangular(7 ** i - 1)  # biggest triangles
        count += (triangular(7) - 1) * triangular_count[i - 1]  # smaller 
        triangular_count.append(count)

    # calculate divisible with whole triangles
    n = limit_conversion[-1]

    divisible += triangular(n) * triangular_count[-1]  # smaller triangles
    divisible += triangular(n-1) * triangular(7 ** (highest_power) - 1)

    # calculate divisible with leftover partial triangles (brute force)
    row = n * 7 ** highest_power
    conv = list(num_to_base(row, 7))  # base 7 conversion of row number

    for i in range(row + 1, limit + 1):
        div_row = 1  # number of divisible numbers in row

        for j in conv:  # calculate divisible nums 
            div_row *= j + 1
            
        divisible += i - div_row
        conv = base_add_one(conv, 7)

    # print result
    not_divisible = total_nums - divisible
    print("Rows not divisible by 7:", not_divisible)


if __name__ == "__main__":
    main()
