def problem141A() -> str:
    def getFrequency(s: str) -> dict[str, int]:
        frequencies = {}
        for char in s:
            if char not in frequencies:
                frequencies[char] = 1
            else:
                frequencies[char] += 1

        return frequencies

    a = input()
    b = input()
    c = input()
    pile = getFrequency(a + b)
    needed_letters = getFrequency(c)

    if pile == needed_letters:
        return "YES"
    return "NO"

print(problem141A())