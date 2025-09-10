def problem20A() -> str:
    given_path = input()
    result = []
    is_root = True

    for char in given_path:
        if not result:
            result.append(char)
            continue
        if char == "/" and result[-1] == "/":
            continue
        is_root = False  # if not slash, not root directory
        result.append(char)

    if not is_root:
        while result[-1] == "/":    
            result.pop()

    return "".join(result)

print(problem20A())