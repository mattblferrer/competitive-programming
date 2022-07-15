def collatz(n):
    steps = 0  # number of steps
    while n != 1:
        if n % 2 == 0:
            n //= 2
        elif n % 2 == 1:
            n = 3 * n + 1
        steps += 1
    return steps


limit = 1000000  # only numbers below this limit will be checked
longestSequence = 0  # largest number of steps to get to 1
longestStartNum = 0  # starting number with the largest number of steps

for i in range(2, limit):
    currentSequence = collatz(i)
    if currentSequence > longestSequence:
        longestStartNum = i
        longestSequence = currentSequence

print(longestStartNum)
print("Sequence: " + str(longestSequence))
