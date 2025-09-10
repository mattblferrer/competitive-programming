from functools import cache


@cache
# returns the number of steps of the Collatz sequence for n to return to 1
def collatz(n: int) -> int:
    if n == 1:
        return 0
    n = n // 2 if n % 2 == 0 else 3*n + 1  # calculate next term
    steps = 1 + collatz(n)  # recursively call collatz(n) for next term
    return steps


def main():
    # declare variables
    limit = 1000000  # only numbers below this limit will be checked
    longest_sequence = 0  # largest number of steps to get to 1
    longest_start_num = 0  # starting number with the largest number of steps

    # for n < limit / 2, 2n will have 1 more Collatz step than n
    for i in range(limit // 2, limit):
        current_sequence = collatz(i)
        if current_sequence > longest_sequence:
            longest_sequence, longest_start_num  = current_sequence, i

    # print result
    print(longest_start_num)
    print(f"Sequence: {longest_sequence}")


if __name__ == "__main__":
    main()

