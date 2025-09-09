def problem172A() -> int:
    n = int(input())
    prefix = input()
    prefix_len = len(prefix)

    for _ in range(n - 1):
        number = input()
        for i in range(prefix_len, -1, -1):
            if number[:i] == prefix[:i]:
                prefix_len = i
                prefix = number[:i]
                break

    return prefix_len

print(problem172A())