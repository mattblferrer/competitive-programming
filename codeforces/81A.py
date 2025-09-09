def problem81A() -> str:
    string = input()
    stack = []

    for char in string:
        if not stack:
            stack.append(char)
        elif char == stack[-1]:
            stack.pop()
        else:
            stack.append(char)

    return "".join(stack)

print(problem81A())