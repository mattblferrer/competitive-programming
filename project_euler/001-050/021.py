def sum_factors(num: int) -> int:  # returns the sum of the factors of num
    factor_sum = 1
    check = num

    for i in (2, 3):  # for 2 and 3
        power = i
        c_factor = 1

        while num % i == 0:
            c_factor += power
            num //= i
            power *= i

        factor_sum *= c_factor

    for i in range(5, int(num ** 0.5) + 3, 6):  # for 6k +- 1
        if i*i > num:
            break

        for j in (0, 2):  # 6k +- 1
            power = (i + j)
            c_factor = 1
            while num % (i + j) == 0:
                c_factor += power
                num //= (i + j)
                power *= (i + j)

            factor_sum *= c_factor

    if num != 1:
        factor_sum *= num + 1

    return factor_sum - check


def main():
    limit = 10000  # given parameter
    amic_sum = 0  # sum of amicable numbers up to limit

    for b in range(2, limit):
        a = sum_factors(b)
        if sum_factors(a) == b and a != b:
            amic_sum += b

    # print result
    print(f"The sum of all amicable numbers below {limit} is {amic_sum}")


if __name__ == "__main__":
    main()
