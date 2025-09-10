def problem1542A() -> str:
    _ = input()  # length of multiset
    multiset = list(map(int, input().split(" ")))
    evens, odds = 0, 0  # only way to make odd = even + odd

    for n in multiset:
        if n % 2 == 0:
            evens += 1
        else:
            odds += 1

    if evens == odds:
        return "Yes"
    return "No"    

test_cases = int(input())
for _ in range(test_cases):
    print(problem1542A())