from math import gcd


def lcm_arr(arr: list[int]) -> int:
    """returns the least common multiple of an array of numbers"""
    lcm = 1
    for i in arr:
        lcm = lcm * i // gcd(lcm, i)
    return lcm


def main():
    def P(s: int, N: int) -> int:
        """returns the number of integers 1 < n < N for which streak(n) = s"""
        return (N - 2) // lcm_list[s] - (N - 2) // lcm_list[s + 1]


    # declare variables
    limit = 4**31
    sum_p = 0

    # generate list of LCMs of n in range(1, n + 1) for P(s, N) function
    lcm = 1
    lcm_list = [1, 1]
    ctr = 2
    while lcm < limit:
        lcm = lcm_arr([i for i in range(1, ctr + 1)])
        lcm_list.append(lcm)
        ctr += 1

    # print result
    sum_p = sum(P(i, 4**i) for i in range(1, 32))
    print(sum_p)


if __name__ == "__main__":
    main()
