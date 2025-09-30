def problem472A() -> None:
    n = int(input())
    if n % 2 == 0:
        print(8, n - 8)  # both divisible by 2
    else:
        print(9, n - 9)  # 9 = 3 * 3, n - 9 is divisible by 2
    
problem472A()