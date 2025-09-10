def main():
    # generate list of d(n) up to limit
    u = 100_000_000
    k = 100_000

    divisor_num_list = [1] * (u + 2)
    for n in range(2, u + 1):
        for div in range(n, u + 1, n):  # multiples of n
            divisor_num_list[div] += 1

    # starting variables for M(n, k)
    low = divisor_num_list[1]
    high = divisor_num_list[k + 1]
    maximum = max(divisor_num_list[1: k + 1])
    sum_s = maximum

    # calculate S(u, k) for n from 1 <= n <= u - k + 1
    for n in range(2, u - k + 2):
        low = divisor_num_list[n - 1]
        high = divisor_num_list[n + k - 1]
        
        # check for maximum in new subarray
        if high > maximum >= low:
            maximum = high
        elif maximum <= low:
            maximum = max(divisor_num_list[n: n + k])
        sum_s += maximum

    # print result
    print(sum_s)


if __name__ == "__main__":
    main()
