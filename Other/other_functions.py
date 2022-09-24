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