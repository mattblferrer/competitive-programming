def problem1352A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        n = input()
        round_numbers = []

        for i, digit in enumerate(n[::-1]):  # from right to left
            if digit != "0":
                round_numbers.append(int(digit) * 10**i)

        print(len(round_numbers)) 
        print(*round_numbers[::-1])

problem1352A()