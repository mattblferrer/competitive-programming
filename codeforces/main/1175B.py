def problem1175B() -> None:
    l = int(input())
    stack = [1]  # stores for loop n's (default = 1)
    limit = 2 ** 32
    x = 0
 
    for _ in range(l):
        line = input()
        command = line[:3]  # first 3 characters (add, for, end)
        
        if command == "add":
            x += stack[-1]
        elif command == "for":
            n = int(line[4:])
            stack.append(min(limit, n * stack[-1]))
        elif command == "end":
            stack.pop()
        if x >= limit:
            print("OVERFLOW!!!")
            return
    print(x)
 
problem1175B()