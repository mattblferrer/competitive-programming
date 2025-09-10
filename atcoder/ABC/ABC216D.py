def ABC216D() -> str:
    # get input m cylinders
    n, m = map(int, input().split())
    a = []
    balls = 2 * n
    for _ in range(m):
        k_i = int(input())
        a_i = list(map(int, input().split()))
        a.append(a_i)

    # get indices of every ball at the top of their cylinder
    top = [[] for _ in range(n + 1)]
    for i, a_i in enumerate(a):
        top[a_i[-1]].append(i)
    
    # queue of which balls have two of the same color at top of cylinder
    to_take = [(i, v) for i, v in enumerate(top) if len(v) == 2]
    while to_take:
        ball, indices = to_take.pop()
        for i in indices:  # remove balls from top of both stacks
            a[i].pop()
            if not a[i]:
                continue
            top[a[i][-1]].append(i)  # update top with new balls
            if len(top[a[i][-1]]) == 2:  # add new balls to queue
                to_take.append((a[i][-1], top[a[i][-1]]))
        balls -= 2

    # check if all balls have been taken
    if balls == 0:
        return "Yes"
    return "No"

print(ABC216D())