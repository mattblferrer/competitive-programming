def problem630R() -> int:
    n = int(input())
    if n % 2 == 0:
        return 2
    else:
        return 1
    
print(problem630R())