def problem69A() -> str:
    vectors = int(input())
    x_sum, y_sum, z_sum = 0, 0, 0

    for _ in range(vectors):  # add all vectors (x, y, z)
        x, y, z = map(int, input().split(' '))
        x_sum += x
        y_sum += y
        z_sum += z
        
    if x_sum == 0 and y_sum == 0 and z_sum == 0:  # equilibrium
        return "YES"
    return "NO"
    
print(problem69A())