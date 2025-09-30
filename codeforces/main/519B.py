def problem519B() -> tuple[int, int]:
    _ = input()
    first_compile = sum(map(int, input().split(" ")))
    second_compile = sum(map(int, input().split(" ")))
    third_compile = sum(map(int, input().split(" ")))
    return first_compile - second_compile, second_compile - third_compile

print(*problem519B(), sep="\n")