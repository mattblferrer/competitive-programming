from functools import cache


# pre-computed list of all factorials 0-9
factorials = (1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880) 
@cache
def fac_digit_sum(num: int) -> int:
    """returns the sum of the factorials of the digits of num"""
    return sum([factorials[int(digit)] for digit in str(num)])


def fac_digit_chain(num: int) -> int:
    """returns the length of the factorial sum chain of num"""
    current_chain = []
    counter = 0
    current_sum = num

    while current_sum not in current_chain:
        current_chain.append(current_sum)
        current_sum = fac_digit_sum(current_sum)
        counter += 1

    return counter


def main():
    limit = 1_000_000  # declare limit variable
  
    # loop through numbers up to limit
    answer = sum(1 for i in range(limit) if fac_digit_chain(i) == 60)

    # print result
    print(f"The number of chains that have 60 non-repeating terms: {answer}")


if __name__ == "__main__":
    main()
