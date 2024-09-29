def problem1850A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        nums = sorted(list(map(int, input().split(" "))))
        if nums[1] + nums[2] >= 10:
            print("YES")
        else:
            print("NO")

problem1850A()