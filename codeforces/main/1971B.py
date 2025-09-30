def problem1971B() -> None:
    string = list(input())
    asc = sorted(string)
    desc = sorted(string, reverse=True)

    if string == asc and string == desc:  # not possible to make different str
        print("NO")
        return None

    print("YES")
    if string != asc:
        print("".join(asc))
    else:
        print("".join(desc))

test_cases = int(input())
for _ in range(test_cases):
    problem1971B()