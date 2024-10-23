def CSES2165() -> list[str]:
    def move(n: int, start: int, middle: int, end: int) -> list[str]:
        if n == 0:
            return []
        moves = []
        moves.extend(move(n - 1, start, end, middle))
        moves.append(f"{start} {end}")
        moves.extend(move(n - 1, middle, start, end))
        return moves

    n = int(input())
    moves = move(n, 1, 2, 3)
    print(len(moves))
    return moves

print(*CSES2165(), sep="\n")