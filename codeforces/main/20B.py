def problem20B() -> None:
    a, b, c = map(int, input().split())
    if a == 0:
        if b == 0:
            if c == 0:  # 0 = 0
                print(-1)
            else:  # non-zero = 0
                print(0)
        else:
            if c == 0:  # Bx = 0
                print(1)
                print(format(0, "05f"))
            else:  # Bx + C = 0
                print(1)
                print(format(-c / b, "05f"))

    else:  # Ax^2 + Bx + C = 0
        disc = (b * b - 4 * a * c)
        root_1 = (-b - disc ** 0.5) / (2 * a)
        root_2 = (-b + disc ** 0.5) / (2 * a)
        
        if disc < 0:  # no real roots
            print(0)
        elif disc == 0:  # one real root
            print(1)
            print(format(root_1, "05f"))
        else:  # two real roots
            print(2)
            print(format(min(root_1, root_2), "05f"))
            print(format(max(root_1, root_2), "05f"))

problem20B()