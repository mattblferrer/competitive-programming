from functools import cache


@cache
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
    n = 15474  # given + 2 (n has to be even)
    limit = 1_000_000
    max_chain_length = 5  # given
    max_chain = []  # stores the longest possible amicable 
    output = 0  # smallest element of the longest amicable chain

    # main loop
    while n < limit:
        test_n = sum_factors(n)  # this will be the chain variable
        current_chain = [n]  # the current n will be initialized in the chain

        while test_n != 1:  # if 1, then it hit a prime number
            if test_n == n:  # if chain looped back to the start
                # check for chain length
                if len(current_chain) < max_chain_length:
                    break
                max_chain_length = len(current_chain)
                max_chain = current_chain
                output = min(current_chain)

            if test_n in current_chain:
                break
            if test_n > limit:  # if it exceeded 1 million
                break

            current_chain.append(test_n)
            test_n = sum_factors(test_n)
                
        n += 2

    # print output
    print(f"The smallest member of the longest amicable chain with no "\
        f"element exceeding {limit} is {output}")
    print(f"Longest chain: {max_chain}")
    print(f"Length of longest chain: {max_chain_length}")


if __name__ == "__main__":
    main()
