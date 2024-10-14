def CSES2205() -> None:
    def gray_code(n: int) -> list[str]:
        if n == 1:
            return ['0', '1']
        first = ['0' + code for code in gray_code(n - 1)]
        second = ['1' + code for code in reversed(gray_code(n - 1))]
        return first + second
        
    n = int(input())
    print(*gray_code(n), sep="\n")

CSES2205()