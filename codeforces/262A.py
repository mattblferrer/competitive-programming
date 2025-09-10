def problem262A() -> int:
    n, k = map(int, input().split(' '))
    a = list(input().split())
    result = 0

    for a_i in a:
        lucky_digits = 0
        for digit in a_i:
            if digit in ['4', '7']:
                lucky_digits += 1
        if lucky_digits <= k:
            result += 1

    return result

print(problem262A())