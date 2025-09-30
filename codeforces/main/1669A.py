def problem1669A() -> None:
    test_cases = int(input())

    for _ in range(test_cases):
        rating = int(input())
        if rating <= 1399:
            print("Division 4")
        elif 1400 <= rating <= 1599:
            print("Division 3")
        elif 1600 <= rating <= 1899:
            print("Division 2")
        else:
            print("Division 1")

problem1669A()