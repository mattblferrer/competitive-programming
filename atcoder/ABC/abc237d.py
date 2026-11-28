from collections import deque

def ABC237D() -> list[int]:
    n = int(input())
    commands = input()
    a = deque([n])

    for i in range(n - 1, -1, -1):
        if commands[i] == "L":
            a.append(i)
        elif commands[i] == "R":
            a.appendleft(i)

    return list(a)

print(*ABC237D())