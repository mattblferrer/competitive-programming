def problem148A() -> int:
    def isDamaged(modulus: list[int], dragon: int) -> bool:
        for m in modulus:
            if dragon % m == 0:
                return True
            
        return False

    k = int(input())
    l = int(input())
    m = int(input())
    n = int(input())
    d = int(input())
    damaged = 0  # number of damaged dragons

    for dragon in range(1, d + 1):
        if isDamaged([k, l, m, n], dragon):
            damaged += 1

    return damaged

print(problem148A())