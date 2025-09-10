def problem637B() -> None:
    n = int(input())  # number of messages
    message_index = {}

    for i in range(n):  # get index of message (later = higher index)
        name = input()
        message_index[name] = i

    sorted_msgs = sorted([(i, name) for name, i in message_index.items()])
    for i, name in reversed(sorted_msgs):  # sort from last to first
        print(name)

problem637B()