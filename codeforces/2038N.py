def problem2038N() -> str:
    s = input()
    if int(s[0]) < int(s[2]):
        return f"{s[0]}<{s[2]}"
    if int(s[0]) == int(s[2]):
        return f"{s[0]}={s[2]}"
    if int(s[0]) > int(s[2]):
        return f"{s[0]}>{s[2]}"

test_cases = int(input())
for _ in range(test_cases):
    print(problem2038N())