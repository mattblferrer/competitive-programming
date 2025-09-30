def problem931A() -> int:
    a = int(input())
    b = int(input())
    diff = abs(a - b)
    if diff % 2 == 0:  # both friends use same tiredness
        return (diff // 2) * (diff // 2 + 1)
    else:  # one friend is more tired
        return (diff // 2) * (diff // 2 + 1) + diff // 2 + 1

print(problem931A())