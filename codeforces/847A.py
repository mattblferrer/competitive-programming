def problem847A() -> list[tuple[int, int]]:
    # get input as l_i, r_i and convert to l_i, i, r_i nodes
    n = int(input())
    cells = []
    for i in range(1, n + 1):
        l_i, r_i = map(int, input().split(' '))
        cells.append((l_i, i, r_i))

    # get list of all given linked lists 
    lists = []
    for l_i, i, r_i in cells:
        if l_i == 0:  # start of linked list
            curr_list = [i]
            curr_node = l_i, i, r_i
            while curr_node[2] != 0:  # traverse linked list
                curr_list.append(curr_node[2])
                curr_node = cells[curr_node[2] - 1]
            lists.append(curr_list)  # end of linked list

    # unite all linked lists into one linked list
    new_list = [0]
    for l in lists:
        new_list.extend(l)
    new_list.append(0)
    cells = []
    for l_i, i, r_i in zip(new_list, new_list[1:], new_list[2:]):
        cells.append((i, l_i, r_i))

    return [(l_i, r_i) for i, l_i, r_i in sorted(cells)]

result = problem847A()
for l_i, r_i in result:
    print(l_i, r_i)