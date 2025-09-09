def problem266B() -> str:
    n, t = map(int, input().split(" "))
    queue = list(input())  # convert to list so swaps are possible
    for _ in range(t):
        i = 0
        while i < n - 1:  # check adjacent positions in queue
            if queue[i] == "B" and queue[i + 1] == "G":  # swap
                queue[i], queue[i + 1] = "G", "B"
                i += 1
            i += 1

    return "".join(queue)

print(problem266B())