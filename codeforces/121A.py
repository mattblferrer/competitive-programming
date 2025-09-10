def problem121A() -> int:
    # generate all lucky numbers below 10**9 (<= 9 digits)
    lucky_numbers = []
    for i in range(2, 2 ** 10 + 1):
        curr = ""
        for bit in bin(i)[3:]:
            if bit == "0":
                curr += "4"
            else:
                curr += "7"
        lucky_numbers.append(int(curr))

    # get sum of all (next(x)), l <= x <= r
    l, r = map(int, input().split())
    lucky_used = []

    for k in lucky_numbers:
        if k < l:
            continue
        lucky_used.append(k)
        if k >= r:
            break

    sum_next = sum((b - a) * b for a, b in zip(lucky_used, lucky_used[1:]))
    sum_next += (lucky_used[0] - l + 1) * lucky_used[0]  # (l, first lucky]
    sum_next += (r - lucky_used[-1]) * lucky_used[-1]  # (last lucky + 1, r]
    return sum_next

print(problem121A())