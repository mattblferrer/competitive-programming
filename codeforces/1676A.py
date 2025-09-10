def problem1676A() -> None:
    test_cases = int(input())

    for _ in range(test_cases):
        ticket = input()
        first_3 = sum(int(digit) for digit in ticket[0:3])
        last_3 = sum(int(digit) for digit in ticket[3:6])
        
        if first_3 == last_3:  # lucky ticket
            print("YES")
        else:
            print("NO")

problem1676A()