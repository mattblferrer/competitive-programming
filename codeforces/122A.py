def problem58A() -> str:
    def isLucky(n: int) -> bool:
        nstr = str(n)
        for digit in nstr:
            if digit not in ["4", "7"]:
                return False
        return True

    lucky = [n for n in range(1, 1000) if isLucky(n)]
    n = int(input())

    for k in lucky:  # check if evenly divisible by lucky number
        if n % k == 0:
            return "YES"
        
    return "NO"

print(problem58A())