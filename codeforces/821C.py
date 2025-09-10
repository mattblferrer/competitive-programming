def problem821C() -> int:
    n = int(input())
    stack = []
    reorders = 0
    curr = 1

    for _ in range(2 * n):
        line = input()
        if line == "remove":
            if not stack:
                curr += 1
                continue
            if stack[-1] != curr:
                reorders += 1
                stack = []
            else:
                stack.pop()
            curr += 1

        else:  # add
            stack.append(int(line.split()[1]))

    return reorders

print(problem821C())