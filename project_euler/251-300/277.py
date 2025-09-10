def reverse_modified_collatz(steps: str, n: int) -> int:
    """returns the number that outputs n using the Modified Collatz sequence
    with defined steps"""
    for step in reversed(steps):
        if step == "d":
            n = (3 * n + 1) // 2
        elif step == "U":
            n = (3 * n - 2) // 4
        elif step == "D":
            n *= 3

    return n


def modified_collatz(n: int) -> int:
    """returns n after one step of the modified Collatz sequence"""
    if n % 3 == 0:
        return n // 3
    elif n % 3 == 1:
        return (4 * n + 2) // 3
    return (2 * n - 1) // 3


def main():
    # declare variables
    steps = "UDDDUdddDDUDDddDdDddDDUDDdUUDd"
    k = 10**15
    a = 1
    i = 1

    # find lowest a1 reachable via reverse modified Collatz (without using mod)
    while a < k:
        a = reverse_modified_collatz(steps, i)
        i += 1

    # test out candidate a1 to find valid
    while True:
        a = reverse_modified_collatz(steps, i)
        m = a
        for step in steps:  # build string of Collatz seq steps
            remainder = m % 3
            if remainder == 0:
                step_used = "D"
            elif remainder == 1:
                step_used = "U"
            else:
                step_used = "d"

            m = modified_collatz(m)
            if step != step_used:  # check if step matches
                break

        else:  # if steps used matched the steps defined in problem
            break

        i += 1

    # print result
    print(f"{a}, operations: {i}")


if __name__ == "__main__":
    main()
