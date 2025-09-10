# returns the Ackermann function (m, n) with modulo mod ^ modp
def ackermann(m: int, n: int, mod: int, modp: int) -> int:
    if m == 0:
        return (n + 1) % pow(mod, modp)
    elif m == 1:
        return (n + 2) % pow(mod, modp)
    elif m == 2:
        return (2*n + 3) % pow(mod, modp)
    elif m == 3:
        return pow(2, n + 3, pow(mod, modp)) - 3
    elif m == 4:
        # TODO ack(4, n) to ack(6, n)
        pass


def main():
    # declare variables
    n = 6
    mod, modp = 14, 8
    ack_sum = sum(ackermann(i, j, mod, modp) for i in range(n + 1)
        for j in range(n + 1))

    # print result
    print(ack_sum % pow(mod, modp))


if __name__ == "__main__":
    main()
