def Problem1328A() -> None:
    test_cases = int(input())
    for _ in range(test_cases):
        a, b = map(int, input().split(" "))  # get line input from user
        
        if a % b == 0:
            print(0)
        else:
            print(b - (a % b))

if __name__ == "__main__":
    Problem1328A()