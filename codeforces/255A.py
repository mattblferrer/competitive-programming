def problem255A() -> str:
    n = int(input())
    a = list(map(int, input().split()))
    exercises = [0, 0, 0]
    for i, a_i in enumerate(a):
        exercises[i % 3] += a_i

    if max(exercises) == exercises[0]:
        return "chest"
    elif max(exercises) == exercises[1]:
        return "biceps"
    else:
        return "back"

print(problem255A())