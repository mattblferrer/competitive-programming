def main():
    # declare variables
    ctr = 0
    limit = 15
    a, b = 0, 1

    # F(x) * F(x + 1) where x = 2k is a golden nugget                      
    while ctr // 2 < limit:
        a, b = b, a + b
        ctr += 1

    # print result
    print(a * b)


if __name__ == "__main__":
    main()
