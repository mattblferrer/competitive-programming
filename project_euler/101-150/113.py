"""
Numbers below 100 are all non-bouncy.
As the first digit of the number increases, the number of increasing numbers
decreases, while the number of decreasing numbers increases. 

Total non-bouncy numbers = increasing + decreasing numbers

This uses a "recursive" algorithm to get the number of non-bouncy numbers of x
digits from the number of non-bouncy numbers of x-1 digits.
"""

def main():
    # loop to generate number of increasing and decreasing numbers
    # (increasing + decreasing = total non-bouncy numbers)
    arr = list(range(1, 10))
    increasing = 45
    decreasing = 54
    pow10 = 100  # power of 10 in limit

    for i in range(2, pow10):  # 1 digit = 9, 2 digit = 45 inc + 45 dec
        # calculate number of non-bouncy numbers for i digits
        new_arr = []
        current_term = 0

        for j in range(1, 10):
            current_term += sum(arr[:j])
            new_arr.append(sum(arr[:j]))
        
        increasing += current_term
        decreasing += increasing
        arr = new_arr

    # print result
    print(f"Number of non-bouncy: {increasing + decreasing}")


if __name__ == "__main__":
    main()
