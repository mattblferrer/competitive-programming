def problem1676C() -> int:
    def word_difference(word1: str, word2: str) -> int:
        diff = 0
        for a, b in zip(word1, word2):
            diff += abs(ord(b) - ord(a))
        
        return diff

    n, _ = map(int, input().split(" "))
    strings = []

    for _ in range(n):  # get input strings as list
        string = input()
        strings.append(string)

    min_diff = float('inf')
    for i in range(n):  # get differences between every pair strings i and j.
        for j in range(i + 1, n):
            diff = word_difference(strings[i], strings[j])
            min_diff = min(min_diff, diff)

    return min_diff

test_cases = int(input())
for _ in range(test_cases):
    print(problem1676C())