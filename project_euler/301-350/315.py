from math import sqrt


def soe(n: int) -> list[bool]:
    """creates a Sieve of Eratosthenes array of size n"""
    iterlimit = int(sqrt(n)) + 1
    is_prime_list = [True]*n

    # for 0 and 1 
    is_prime_list[0] = is_prime_list[1] = False

    # for 2 and 3
    for i in (2, 3):
        for multiple in range(i*i, n, i):
            # assign multiples of 2 or 3 as not being prime
            is_prime_list[multiple] = False  

    # for 6k +- 1
    for i in range(5, iterlimit+2, 6): 
        for j in (0, 2): 
            for multiple in range((i+j) * (i+j), n, i+j):
                # assign multiples of i+j as not being prime
                is_prime_list[multiple] = False  

    return is_prime_list


def digit_sum(x: int) -> int:
    """returns the sum of the digits of x"""
    return sum(int(i) for i in str(x))


def main():
    def sam_digit_transitions(x: int) -> int:
        """returns the number of 7-segment display transitions needed for 
        Sam's clock to display x"""
        return sum(sam_clock[int(digit_x)] for digit_x in str(x))
        

    def max_digit_transitions(x: int, y: int) -> int:
        """returns the number of 7-segment display transitions needed for 
        Max's clock to switch between x and y, x > y"""
        transitions = 0
        string_x, string_y = str(x), str(y)

        # calculate transitions for common digits
        for digit_x, digit_y in zip(reversed(string_x), reversed(string_y)):
            transitions += max_clock[int(digit_x)][int(digit_y)]

        # calculate transitions to turn off extra digits
        for digit_x in string_x[:len(string_x) - len(string_y)]:
            transitions += sam_clock[int(digit_x)]

        return transitions


    # digit variables (for transitions between Sam and Max's clocks)
    digits = [
    [1,1,1,1,1,1,0], # digit 0
    [0,1,1,0,0,0,0], # digit 1
    [1,1,0,1,1,0,1], # digit 2
    [1,1,1,1,0,0,1], # digit 3
    [0,1,1,0,0,1,1], # digit 4
    [1,0,1,1,0,1,1], # digit 5
    [1,0,1,1,1,1,1], # digit 6
    [1,1,1,0,0,1,0], # digit 7
    [1,1,1,1,1,1,1], # digit 8
    [1,1,1,1,0,1,1], # digit 9
    ]
    sam_clock = [sum(digit) for digit in digits]
    max_clock = [[sum(i ^ j for i, j in zip(x, y)) for x in digits] 
        for y in digits]

    # generate list of primes
    lower_limit = 10**7
    upper_limit = 2 * 10**7
    is_prime_list = soe(upper_limit)
    prime_list = [i for i, isprime in enumerate(is_prime_list) if isprime and
        i > lower_limit]
    maxc = samc = 0  # transition counts for Max and Sam's clocks

    # loop through digit sums
    for x in prime_list:
        initial = sam_digit_transitions(x)
        maxc += initial
        samc += 2 * initial  # on / off on Sam's display

        while x > 9:  # calculate until single digit is reached
            prev_x = x  # store previous digit for transition calculation
            x = digit_sum(x)
            maxc += max_digit_transitions(prev_x, x)
            samc += 2 * sam_digit_transitions(x)  # on / off on Sam's display

        # add transitions to turn off Max's display
        maxc += sam_digit_transitions(x)  

    # print result
    print(f"Sam: {samc}, Max: {maxc}, Difference: {samc - maxc}")


if __name__ == "__main__":
    main()
