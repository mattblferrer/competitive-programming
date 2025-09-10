def problem1722C() -> tuple[int, int, int]:
    a_points, b_points, c_points = 0, 0, 0
    _ = input()
    a_words = set(input().split(' '))
    b_words = set(input().split(' '))
    c_words = set(input().split(' '))
    
    for a in a_words:
        if a not in b_words and a not in c_words:
            a_points += 3
        elif a in b_words and a in c_words:
            continue
        else:
            a_points += 1

    for b in b_words:
        if b not in a_words and b not in c_words:
            b_points += 3
        elif b in a_words and b in c_words:
            continue
        else:
            b_points += 1

    for c in c_words:
        if c not in a_words and c not in b_words:
            c_points += 3
        elif c in a_words and c in b_words:
            continue
        else:
            c_points += 1

    return a_points, b_points, c_points

test_cases = int(input())
for _ in range(test_cases):
    print(*problem1722C())