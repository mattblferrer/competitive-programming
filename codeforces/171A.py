def problem171A() -> int:
    a_1, a_2 = map(int, input().split(' '))
    return a_1 + int(str(a_2)[::-1])  # a_1 + reversed(a_2)

print(problem171A())