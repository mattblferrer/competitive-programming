def problem133A() -> str:
    program = input()
    for char in program:
        if char in 'HQ9':
            return "YES"

    return "NO"

print(problem133A())