def main():
    # function that will return False if the chain ends at 1 and 
    # return True if the chain ends at 89
    def number_chain(num: int) -> int:
        def get_square_sum(num: int) -> int:
            square_sum = 0
            # get digits of num and add their squares to square_sum
            while num:
                digit = num % 10
                square_sum += digit * digit
                num //= 10
            return square_sum


        temp = num = get_square_sum(num)

        while True:
            num = get_square_sum(num)

            if num_ends[num] == 0:
                num_ends[temp] = num_ends[num]
                return False
            elif num_ends[num] == 1:
                num_ends[temp] = num_ends[num]
                return True


    # given parameter
    n = 10_000_000
    num_ends = [-1]*568  # 9^2 * (7 digits) + 1
    num_ends[1], num_ends[89] = 0, 1  # ends of chain

    # iterate output variable from 1 to n
    start_nums = 0
    
    for i in range(1, n):
        start_nums += number_chain(i)

    # print result
    print(f"Starting numbers below {n}: {start_nums}")


if __name__ == "__main__":
    main()
