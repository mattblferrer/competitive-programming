def problem742A() -> int:
    n = int(input())
    if n == 0:  # any x^0 = 1
        return 1
    if n % 4 == 0:  # check remainder of power (since last digit cyclic)
        return 6
    if n % 4 == 1:
        return 8
    if n % 4 == 2:
        return 4
    if n % 4 == 3:
        return 2


if __name__ == "__main__":
    print(problem742A())