def main():
    # declare variables
    n = 10**15
    s = 0
    sqrt = int(n ** 0.5)

    # calculate sum of ssq(n // i) + i^2*(n // i) for i from 1 to sqrt(n)
    for i in range(1, sqrt + 1):
        q = n // i
        s += (q * (q + 1) * (2*q + 1)) // 6 + i*i*q 

    # print result
    s -= (sqrt * sqrt * (sqrt + 1) * (2 * sqrt + 1)) // 6
    print(s % 10**9)


if __name__ == "__main__":
    main()
