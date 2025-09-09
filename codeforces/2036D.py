def problem2036D() -> int:
    n, m = map(int, input().split(' '))
    carpet = [list(map(int, list(input()))) for _ in range(n)]
    layers = []

    # expand layers of the carpet into list form
    for k in range(min(n, m) // 2):
        layer = carpet[k][k:len(carpet[-1]) - k]  # top
        for i in range(1 + k, len(carpet) - 1 - k):  # right
            layer.append(carpet[i][-k - 1])
        layer.extend(carpet[-k - 1][k:len(carpet[-1]) - k][::-1])  # bottom
        for i in range(len(carpet) - 2 - k, k, -1):  # left
            layer.append(carpet[i][k])
        layers.append(layer)

    # count occurrences of 1543 in each layer
    count = 0
    for layer in layers:
        l = len(layer)
        for i in range(l):
            if (layer[i] == 1 and layer[(i + 1) % l] == 5 
                and layer[(i + 2) % l] == 4 and layer[(i + 3) % l] == 3):
                count += 1

    return count

test_cases = int(input())
for _ in range(test_cases):
    print(problem2036D())