def problem1207A() -> int:
    b, p, f = map(int, input().split(" "))
    h, c = map(int, input().split(" "))

    max_burgers = b // 2
    profit = 0
    if h > c:  # more profitable to sell hamburgers
        profit += min(p, max_burgers) * h
        max_burgers -= min(p, max_burgers)
        if max_burgers:  # if buns leftover, sell remaining chicken burgers
            profit += min(f, max_burgers) * c
            max_burgers -= min(f, max_burgers)

    else:  # more profitable to sell chicken burgers
        profit += min(f, max_burgers) * c
        max_burgers -= min(f, max_burgers)
        if max_burgers:  # if buns leftover, sell remaining hamburgers
            profit += min(p, max_burgers) * h
            max_burgers -= min(p, max_burgers)

    return profit

test_cases = int(input())
for _ in range(test_cases):
    print(problem1207A())