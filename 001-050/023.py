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
    # declare variables
    limit = 28123  # given parameter
    can_be_sum = [False]*(limit + 1)
    abundant_list = [i for i in range(2, limit) if sum_factors(i) > i]

    # calculate all numbers that can be sum of two abundant numbers
    for i in abundant_list:  
        for j in abundant_list:
            if i+j > limit:
                break
            can_be_sum[i+j] = True

    # sum of all the positive integers that can't be expressed as the sum of 
    # two abundant numbers
    non_abundant_sum = sum(idx for idx, x in enumerate(can_be_sum) if not x)

    # print result
    print("The sum of all positive integers that can't be written as the "\
        f"sum of two abundant numbers is {non_abundant_sum}")


if __name__ == "__main__":
    main()
