def problem1520A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        _ = input()  # number of days Polycarp solved tasks
        tasks = input()
        seen = set()
        previous_task = ""

        for t in tasks:
            if previous_task == t:  # continuing task
                continue
            if t in seen:  # returning to task, therefore suspicious
                print("NO")
                break
            seen.add(t)
            previous_task = t
        else:  # never returned to task, not suspicious
            print("YES")

problem1520A()