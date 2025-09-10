def problem1950C() -> str:
    hh, mm = map(int, input().split(":"))
    if hh > 12:  # PM
        return f"{hh - 12:02}:{mm:02} PM"
    elif hh == 12:  # 12:xx PM
        return f"{hh:02}:{mm:02} PM"
    elif hh > 0:  # AM
        return f"{hh:02}:{mm:02} AM" 
    else:  # 12:xx AM
        return f"12:{mm:02} AM"

test_cases = int(input())
for _ in range(test_cases):
    print(problem1950C())