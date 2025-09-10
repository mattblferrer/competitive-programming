def problem1593A() -> None:
    candidates = list(map(int, input().split(" ")))
    sort_candidates = sorted(candidates)
    winner = sort_candidates[2]
    runner_up = sort_candidates[1]

    for c in candidates:
        if c == winner:
            if runner_up == winner:  # tie, runner up also should be overtaken
                print(1, end=" ")
            else:  # no tie, winner needs no more votes 
                print(0, end=" ")
        else:
            print(winner + 1 - c, end=" ")   
    print("")  # new line

test_cases = int(input())
for _ in range(test_cases):
    problem1593A()