def problem228A() -> int:
    colors = input().split(" ")
    return 4 - len(set(colors))
  
print(problem228A())