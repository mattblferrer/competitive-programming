def problem127A() -> float:
    def distance(x1: int, y1: int, x2: int, y2: int) -> float:
        return ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5

    n, k = map(int, input().split(' '))
    signature = []

    for _ in range(n):
        x_i, y_i = map(int, input().split(' '))
        signature.append((x_i, y_i))

    total_distance = 0
    for (x1, y1), (x2, y2) in zip(signature, signature[1:]):
        total_distance += distance(x1, y1, x2, y2)
    
    return k * total_distance / 50

print(problem127A())