def problem892A() -> str:
    n = int(input())
    a = list(map(int, input().split(' ')))
    b = sorted(list(map(int, input().split(' '))))

    max_1, max_2 = b[-1], b[-2]  # get biggest two cans
    if sum(a) <= max_1 + max_2:
        return "YES"
    else:
        return "NO"

print(problem892A())