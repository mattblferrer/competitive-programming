def problem1294C() -> None:
    n = int(input())
    for a in range(2, int(n ** (1/3)) + 2):
        if n % a == 0:
            break
    else:
        print("NO")
        return

    n //= a
    for b in range(a + 1, int(n ** (1/2)) + 2):
        if n % b == 0:
            c = n // b
            if c != b and c != a and b != a:  # equality condition
                print("YES")
                print(a, b, c)
                return
    else:
        print("NO")
        return

test_cases = int(input())
for _ in range(test_cases):
    problem1294C()