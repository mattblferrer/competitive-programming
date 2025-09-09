def problem200B() -> float:
    _ = input()  # number of drinks in fridge
    p = list(map(int, input().split(" ")))  # drinks in fridge
    total_oj = 0  # total amount of orange juice

    for p_i in p:
        total_oj += p_i
    
    return total_oj / len(p)

print(problem200B())