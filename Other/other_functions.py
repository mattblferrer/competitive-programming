from math import sqrt

# returns the convergents of sqrt(num)
def convergent_terms(num: int, bound: int) -> tuple[list[int]]:
    sqrt_num = sqrt(num) % 1  # fractional part only
    n, d, k = int(sqrt(num)), 1, 1
    n_arr, d_arr = [n], [1]
    a = [n]

    while d < bound:
        # get continued fraction expansion terms a
        sqrt_num = 1 / sqrt_num
        a.append(int(sqrt_num))
        sqrt_num -= int(sqrt_num)

        # get convergent terms p/q
        if k == 1:
            n = a[0]*a[1] + 1
            d = a[1]
        else:
            n = a[k]*n_arr[k-1] + n_arr[k-2]
            d = a[k]*d_arr[k-1] + d_arr[k-2]

        n_arr.append(n)
        d_arr.append(d)
        k += 1

    return n_arr, d_arr


# adds 1 to base b array
def base_add_one(num_arr: int, b: int) -> list[int]:
    num_arr[0] += 1

    for i in range(len(num_arr)):
        if num_arr[i] >= b:
            num_arr[i] = 0
            if i == len(num_arr) - 1:  # array is too short for carry
                num_arr.insert(len(num_arr), 1)
            else:  # carry over digit > base
                num_arr[i + 1] += 1
        
        else:
            return num_arr
    return num_arr


# code for profiling
import cProfile
import pstats

with cProfile.Profile() as pr:
    pass  # code

stats = pstats.Stats(pr)
stats.sort_stats(pstats.SortKey.TIME)
stats.print_stats()
