def problem749A() -> None:
    n = int(input())
    print(n // 2)  # number of primes 
    if n % 2 == 0:
        print("2 " * (n // 2))
    else:
        print("2 " * (n // 2 - 1) + "3")

problem749A()