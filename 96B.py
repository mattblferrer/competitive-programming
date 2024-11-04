def problem96B() -> int:
    # generate all lucky numbers below limit 10**9 (<= 9 digits)
    lucky_numbers = [47]
    i = 2

    while lucky_numbers[-1] <= 10**9:
        curr = ""
        for bit in bin(i)[3:]:
            if bit == "0":
                curr += "4"
            else:
                curr += "7"

        i += 1
        if curr.count("4") != curr.count("7"):  # super lucky check
            continue
        lucky_numbers.append(int(curr))

    # find lowest lucky number above n 
    n = int(input())
    for l in lucky_numbers:
        if l >= n:
            return l

print(problem96B())