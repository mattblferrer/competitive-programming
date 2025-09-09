def problem278A() -> int:
    n = int(input())  # number of stations on the line
    distances = list(map(int, input().split(" ")))
    s, t = map(int, input().split(" "))
    
    right = sum(distances[min(s, t) - 1: max(s, t) - 1])  # since 1-indexed
    left = sum(distances) - right
    return min(left, right)

print(problem278A())