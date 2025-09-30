def problem4C() -> None:
    n = int(input())
    seen = {}

    for _ in range(n):
        name = input()
        if name in seen:
            print(name + str(seen[name]))
            seen[name] += 1
        else:
            print("OK")
            seen[name] = 1
        
problem4C()