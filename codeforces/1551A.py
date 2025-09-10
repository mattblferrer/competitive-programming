def problem1551A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        n = int(input())  # number of burles to pay
        c_1, c_2 = n // 3, n // 3
        if n % 3 == 1:  # 1 burle left over
            c_1 += 1
        elif n % 3 == 2:  # 2 burles left over
            c_2 += 1

        print(c_1, c_2)

problem1551A()