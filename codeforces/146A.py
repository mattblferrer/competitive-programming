def problem146A() -> str:
    n = int(input())
    ticket = input()

    # check if ticket's number is a lucky number
    for digit in ticket:
        if digit not in ["4", "7"]:
            return "NO"

    # check if sum of first n / 2 digits = sum of last n / 2 digits
    left, right = ticket[:n // 2], ticket[n // 2:]
    if sum(int(digit) for digit in left) == sum(int(digit) for digit in right):
        return "YES"
    return "NO"

print(problem146A())