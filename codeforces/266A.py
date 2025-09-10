def problem266A() -> int:
    _ = input()  # number of stones = length of string
    stones = input()
    to_remove = 0

    for a, b in zip(stones, stones[1:]):
        if a == b:  # remove one stone if adjacent stones are the same
            to_remove += 1

    return to_remove

print(problem266A())