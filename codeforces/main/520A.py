def problem520A() -> None:
    _ = input()  # length of string
    string = input().lower()
    if len(set(string)) == 26:  # is pangram
        print("YES")
    else:
        print("NO")

problem520A()