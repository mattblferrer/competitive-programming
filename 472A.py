def problem472A() -> None:
    n = int(input())
    if n % 3 == 0:
        print(6, n - 6)  # both divisible by 3
    elif n % 3 == 1:
        print(4, n - 4)  # since 4 mod 3 = 1, if n mod 3 = 1, n - 4 mod 3 = 0
    elif n % 3 == 2:
        print(8, n - 8)  # since 8 mod 3 = 2, if n mod 3 = 2, n - 8 mod 3 = 0
    
problem472A()