def problem1650B() -> int:
    def f_a(x: int, a: int) -> int:
        return x // a + x % a

    l, r, a = map(int, input().split(" "))
    if l // a == r // a:
        return f_a(r, a)
    else:
        return max(f_a(r - r % a - 1, a), f_a(r, a))
    

test_cases = int(input())
for _ in range(test_cases):
    print(problem1650B())