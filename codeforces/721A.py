def problem721A() -> list[int]:
    _ = int(input())
    row = input()
    crossword = []
    length = 0

    for square in row:
        if square == "B":
            length += 1
        else:
            if length:
                crossword.append(length)
            length = 0
    if length:
        crossword.append(length)

    print(len(crossword))
    return crossword

print(*problem721A())