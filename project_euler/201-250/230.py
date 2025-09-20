# returns the Fibonacci sequence as a generator
def fibonacci_generator():
    a, b = 0, 1

    while True:
        a, b = b, a + b
        yield a


def main():
    # returns True if letter at the Fibonacci word index is B, False otherwise
    def fibonacci_word_index(n: int) -> bool:
        # locate first Fibonacci number greater than n, with its index
        for idx_start, f in enumerate(fib):
            if f > n:
                break

        # if parity == 0, subsequence at idx starts with A, else starts with B
        parity = idx_start % 2

        # iterate downwards until subsequence of length 1 is reached
        for idx, f in reversed(list(enumerate(fib[:idx_start + 1]))): 
            while n > 0:
                if n < fib[idx - 2]:  # keep left side
                    idx -= 2
                    
                else:  # keep right side
                    n -= fib[idx - 2]
                    idx -= 1  
                    parity = idx % 2  # parity changes after keeping right

        return parity


    # declare variables
    n_limit = 17
    a = "141592653589793238462643383279502884197169399375105820974"\
        "9445923078164062862089986280348253421170679"
    b = "821480865132823066470938446095505822317253594081284811174"\
        "5028410270193852110555964462294895493038196"
    digit_limit = ((127 + 19*n_limit) * 7**n_limit) // 100  # length of a, b
    fib = []
    sum_n = 0

    # generate Fibonacci numbers up to digit limit
    for term in fibonacci_generator():
        fib.append(term)
        if term > digit_limit:
            break

    # iterate through n's up to n limit
    for n in range(n_limit + 1):
        value = ((127 + 19*n) * 7**n)  # place of digit
        word = fibonacci_word_index(value // 100)

        if word:  # B
            sum_n += 10**n * int(b[(value - 1) % 100])
        else:  # A
            sum_n += 10**n * int(a[(value - 1) % 100])

    # print result
    print(f"{sum_n}")


if __name__ == "__main__":
    main()
