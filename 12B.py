def problem12B() -> str:
    n = input()  # take inputs as string
    m = input()
    sorted_n = list(sorted(n))
    if sorted_n[0] == '0':
        for i, digit in enumerate(sorted_n):  # find first non-zero digit
            if digit != '0':  # if non-zero, swap with first digit
                sorted_n[i], sorted_n[0] = sorted_n[0], sorted_n[i]
                break
                
    n = "".join(sorted_n)  # convert back to string
    if n == m:
        return "OK"
    return "WRONG_ANSWER"

print(problem12B()) 