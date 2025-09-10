def problem467A() -> int:
    rooms = int(input())
    available = 0  # number of rooms available for both George and Alex

    for _ in range(rooms):
        p_i, q_i = map(int, input().split(" "))
        if q_i >= p_i + 2:
            available += 1

    return available

print(problem467A())