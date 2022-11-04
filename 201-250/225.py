def main():
    # declare variables
    limit = 124
    n = 3
    ctr = 0

    # loop through all odds n and calculate tribonacci mod n
    while True:
        a, b, c = 1, 1, 1
        not_repeating = True

        while not_repeating:
            a, b, c = b, c, (a+b+c) % n

            if not c:  # if divisible by n
                break

            # if sequence mod n repeats, no a, b, c will be divisible by n
            if a == 1 and b == 1 and c == 1:  
                not_repeating = False

        else:  # if not divisible by n
            ctr += 1
            if ctr >= limit:
                break

        n += 2

    # print result
    print(f"The {limit}th odd number that does not divide any terms is {n}")


if __name__ == "__main__":
    main()
