def problem116A() -> int:
    test_cases = int(input())
    max_capacity = 0
    curr_people = 0  # current number of people in the tram

    for _ in range(test_cases):
        a_i, b_i = map(int, input().split(" "))  # a = exit, b = enter
        curr_people += b_i - a_i
        max_capacity = max(max_capacity, curr_people)

    return max_capacity


if __name__ == "__main__":
    print(problem116A())