"""
Algorithm explained in: http://www.devalco.de/quadr_Sieb_4x%5E2+1.php 
"""
def main():
    # declare variables
    limit = 10_000_000
    x_list = [4*i*i + 1 for i in range(1, limit + 1)]  # list of 4i^2 + 1
    factor_list = [0] * limit  # list of maximum prime factors

    # sieve through k = +- i + mx where m is integer, x = 4i^2 + 1
    for i, x in enumerate(x_list, start=1):
        if x == 1:
            continue

        for idx in range(i - 1, limit, x):  # +i + kx divisible by x
            if factor_list[idx] < x:  # get maximum prime factor
                factor_list[idx] = x
                
            while x_list[idx] % x == 0:
                x_list[idx] //= x

        for idx in range(max(x - i - 1, 0), limit, x):  # -i + kx
            if factor_list[idx] < x:  # get maximum prime factor
                factor_list[idx] = x

            while x_list[idx] % x == 0:
                x_list[idx] //= x

    # print result (last 18 digits)
    print(sum(factor_list) % 10**18)


if __name__ == "__main__":
    main()
    