def problem74A() -> str:
    n = int(input())
    participants = {}

    for _ in range(n):
        handle, plus, minus, a, b, c, d, e = input().split()
        points = sum(map(int, [int(plus) * 100, -int(minus) * 50, a, b, c, d, e]))
        participants[handle] = points

    maximum = -float('inf')
    for handle, points in participants.items():
        if points > maximum:
            winner = handle
            maximum = points
            
    return winner

print(problem74A())