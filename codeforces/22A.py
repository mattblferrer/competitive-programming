def problem22A() -> None:
    _ = input()  # length of array arr
    arr = sorted(list(set(map(int, input().split(" ")))))  # remove duplicates
    if len(arr) < 2:
        print("NO")
    else:
        print(arr[1])

problem22A()
