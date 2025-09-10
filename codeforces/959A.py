def problem959A() -> str:
    n = int(input())
    if n % 2 == 0:  # even, Mahmoud can win by picking n
        return "Mahmoud"
    else:  # odd, Ehab wins since Mahmoud either cannot pick, or picks n - 1
        return "Ehab"


print(problem959A())