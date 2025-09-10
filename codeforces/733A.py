def problem733A() -> int:
    string = input()
    jump_length = 1
    jump_ability = 1

    for char in string:
        if char in 'AEIOUY':
            jump_length = 1
        else:
            jump_length += 1
        jump_ability = max(jump_ability, jump_length)

    return jump_ability

print(problem733A())