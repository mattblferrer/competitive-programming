def main():
    # declare variables
    p, q = 61, 10**7
    exp = 10  # exponent of modulus

    # random number generator
    s = 290_797  # s0
    n = 0
    power = p  # prime power multiple

    for i in range(1, q + 1):  # exponent of modulus
        s = s * s % 50_515_093  # generate S(n)
        t = s % p  # generate T(n)
        
        # calculate NF(p,q)
        n += t*(power - 1)//(p - 1)  # factors in (T(n)*p^n)!

        if i < exp:  # increment power when lower than modulus
            power *= p

    # print result
    print(n % power) 


if __name__ == "__main__":
    main()
