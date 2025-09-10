def problem1933B() -> int:
    _ = input()  # length of array
    arr = list(map(int, input().split(" ")))
    rem_3_dict = {0:0, 1:0, 2:0}  # dictionary of remainders when divided by 3

    for n in arr:  # get remainders when divided by 3
        rem_3_dict[n % 3] += 1

    remainder = sum(k * v for k, v in rem_3_dict.items()) % 3
    if remainder == 0:  # 0 moves required since already divisible by 3
        return 0
    if rem_3_dict[remainder]:  # remove that element from array
        return 1
    if remainder == 2 and rem_3_dict[remainder - 1]:  # add 1 to that element
        return 1
    return 2

test_cases = int(input())
for _ in range(test_cases):
    print(problem1933B())