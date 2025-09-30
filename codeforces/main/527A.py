def problem527A() -> int:
    a, b = map(int, input().split(' '))
    ships = 0

    while b != 0:
        ships += a // b
        a, b = b, a % b

    return ships
    

print(problem527A())