from functools import cache


@cache
# returns the number of steps of the Collatz sequence for n to return to 1
def collatz(n: int) -> int:
    if n == 1:
        return 0
    n = n // 2 if n % 2 == 0 else 3*n + 1  # calculate next term
    steps = 1 + collatz(n)  # recursively call collatz(n) for next term
    return steps


# declare variables
limit = 1000000  # only numbers below this limit will be checked
longestSequence = 0  # largest number of steps to get to 1
longestStartNum = 0  # starting number with the largest number of steps

# for n < limit / 2, 2n will have 1 more Collatz step than n
for i in range(limit // 2, limit):
    currentSequence = collatz(i)
    if currentSequence > longestSequence:
        longestSequence, longestStartNum  = currentSequence, i

# print result
print(longestStartNum)
print(f"Sequence: {longestSequence}")
