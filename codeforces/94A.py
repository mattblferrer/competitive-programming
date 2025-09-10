def problem94A() -> str:
    password = input()
    encryption = [input() for _ in range(10)]
    original = ""

    for i in range(8):
        for j, code in enumerate(encryption):
            if password[10*i: 10*i + 10] == code:
                original += str(j)
                break

    return original

print(problem94A())