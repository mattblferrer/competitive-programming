def problem1985B() -> int:
    n = int(input())
    max_sum = 0
    for x in range(2, n + 1):  # test sum of multiples for all possible x
        curr_sum = sum(mult for mult in range(x, n + 1, x))
        if curr_sum > max_sum:  # if maximum reached, save x 
            max_sum = curr_sum
            max_x = x

    return max_x

test_cases = int(input())
for _ in range(test_cases):
    print(problem1985B())