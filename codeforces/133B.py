def problem133B() -> int:
    p = input()
    conversion = {
        ">": "1000",
        "<": "1001",
        "+": "1010",
        "-": "1011",
        ".": "1100",
        ",": "1101",
        "[": "1110",
        "]": "1111"
    }
    mod = 10 ** 6 + 3
    converted = "".join(conversion[char] for char in p)
    size = sum(pow(2, i, mod) * int(digit) for i, 
               digit in enumerate(converted[::-1]))
    return size % mod

print(problem133B())