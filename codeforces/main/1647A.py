def problem1647A() -> str:
    def max_num(n: int) -> str:
        base = ["1", "2", "21"]
        if n % 3 == 2:
            return base[(n - 1) % 3] + "12" * ((n - 1) // 3)
        return base[(n - 1) % 3] + "21" * ((n - 1) // 3)
        
    n = int(input())
    return max_num(n)

test_cases = int(input())
for _ in range(test_cases):
    print(problem1647A())