def problem918A() -> str:
    n = int(input())
    fib = [1, 2]
    while fib[-1] < n:  # generate Fibonacci sequence up to n
        fib.append(fib[-1] + fib[-2])

    name = ""
    for i in range(1, n + 1):  # construct new name from Fibonacci 
        if i in fib: 
            name += "O"
        else:
            name += "o"

    return name

print(problem918A())