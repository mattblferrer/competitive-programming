def problem1607A() -> int:
    keys = input()
    word = input()
    key_positions = {key: i for i, key in enumerate(keys)}
    return sum(abs(key_positions[b] - key_positions[a]) 
                    for a, b in zip(word, word[1:]))

test_cases = int(input())
for _ in range(test_cases):
    print(problem1607A())