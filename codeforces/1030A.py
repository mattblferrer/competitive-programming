def problem1030A() -> str:
    _ = input()  # number of people asked for opinions
    opinions = list(map(int, input().split(" ")))
    if sum(opinions) > 0:
        return "HARD"
    return "EASY"

if __name__ == "__main__":
    print(problem1030A())