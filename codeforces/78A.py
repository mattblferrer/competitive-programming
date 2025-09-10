def problem78A() -> str:
    vowels = []

    for _ in range(3):
        line = input()
        line_vowels = 0

        for char in line:  # count number of vowels in line = syllables
            if char in "aeiou":
                line_vowels += 1
        vowels.append(line_vowels)

    if vowels == [5, 7, 5]:
        return "YES"   
    return "NO"

print(problem78A())