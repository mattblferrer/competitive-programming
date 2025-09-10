def problem1399A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        _ = input()  # length of next line
        nums = sorted(list(map(int, input().split(" "))))
        for a, b in zip(nums, nums[1:]):
            if b - a > 1:
                print("NO")
                break

        else:
            print("YES")

problem1399A()