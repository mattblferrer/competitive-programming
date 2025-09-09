def problem25B() -> str:
    n = int(input())
    number = input()
    divided = []

    if n % 2 == 0:  # split into groups of two
        for i, digit in enumerate(number):
            divided.append(digit)
            if i % 2 == 1:
                divided.append("-")

    else:  # first group is group of three
        for i in range(3):  # first group of three
            divided.append(number[i])
        divided.append("-")

        for i, digit in enumerate(number[3:]):  # last groups of two each
            divided.append(digit)
            if i % 2 == 1:
                divided.append("-")

    return "".join(divided)[:-1]  # remove last divider

print(problem25B())