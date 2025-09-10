def problem9C() -> int:
    n = int(input())
    curr = 1
    while int(bin(curr)[2:]) <= n:
        curr += 1
    
    return curr - 1

print(problem9C())