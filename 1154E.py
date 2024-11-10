def problem1154E() -> str:
    n, k = map(int, input().split(' '))
    a = list(map(int, input().split(' ')))
    queue = sorted((a_i, i) for i, a_i in enumerate(a))
    nodes = ([[None, 0, 1]] 
        + [[i - 1, i, i + 1] for i in range(1, n - 1)]
        + [[n - 2, n - 1, None]])  # implement as linked list nodes
    teams = [0] * n
    turn = 1

    while queue:
        # check if next max student is available
        _, i = queue.pop()
        if teams[i]:
            continue
        teams[i] = turn

        # traverse k closest students to the left
        curr_node = nodes[i]
        for _ in range(k):  
            if curr_node[0] is None:
                break
            curr_node = nodes[curr_node[0]]
            teams[curr_node[1]] = turn
        new_left = curr_node[0]

        # traverse k closest students to the right
        curr_node = nodes[i]
        for _ in range(k):  
            if curr_node[2] is None:
                break
            curr_node = nodes[curr_node[2]]
            teams[curr_node[1]] = turn
        new_right = curr_node[2]

        # update closest available student to left and right
        if new_left is not None:
            nodes[new_left][2] = new_right
        if new_right is not None:
            nodes[new_right][0] = new_left
        
        turn = 3 - turn  # switch turn: 1 -> 2, 2 -> 1

    return "".join(map(str, teams))

print(problem1154E())
