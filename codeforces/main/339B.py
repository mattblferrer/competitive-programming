def problem339B() -> int:
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    position = 1
    total_time = 0
    
    for a_i in a:
        if a_i - position >= 0:
            total_time += a_i - position
        else:
            total_time += n - (position - a_i)
        position = a_i

    return total_time

print(problem339B())