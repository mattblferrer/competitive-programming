def problem1607A() -> int:
    keys = input()
    word = input()
    key_positions = {key: i for i, key in enumerate(keys)}
    time_cost = 0

    for a, b in zip(word, word[1:]):  # adjacent letters a, b in word
        time_cost += abs(key_positions[b] - key_positions[a])

    return time_cost

test_cases = int(input())
for _ in range(test_cases):
    print(problem1607A())