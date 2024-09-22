def Problem25A() -> None:
    _ = int(input())
    iq_test = list(map(int, input().split(" ")))  # get input as list
    evens, odds = 0, 0

    for n in iq_test:  # check parity of unique evenness
        if n % 2 == 0:
            evens += 1
        else:
            odds += 1

    for i, n in enumerate(iq_test):
        if odds == 1 and n % 2 == 1:  # check if unique is odd
            return i + 1
        if evens == 1 and n % 2 == 0:  # check if unique is even
            return i + 1
    

if __name__ == "__main__":
    print(Problem25A())