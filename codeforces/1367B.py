def problem1367B() -> int:
    _ = input()  # length of array a
    a = list(map(int, input().split(" ")))

    # check if good array possible
    evens, odds = 0, 0
    for a_i in a:
        if a_i % 2 == 0:
            evens += 1
        else:
            odds += 1

    if not evens == odds and not evens == odds + 1:  # not possible
        return -1
    
    # check how many swaps are needed
    out_of_place = 0
    for i, a_i in enumerate(a):
        if i % 2 != a_i % 2:
            out_of_place += 1

    return out_of_place // 2  # one swap can put two elements in place


test_cases = int(input())
for _ in range(test_cases):
    print(problem1367B())