def problem912A() -> int:
    a, b = map(int, input().split(' '))
    x, y, z = map(int, input().split(' '))
    a_need = 2*x + y
    b_need = y + 3*z
    
    return max(a_need - a, 0) + max(b_need - b, 0)

print(problem912A())