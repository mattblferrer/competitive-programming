def problem427A() -> int:
    _ = input()  # number of events
    events = list(map(int, input().split(" ")))
    recruits = 0
    untreated = 0  # number of crimes that go untreated

    for e in events:
        if e == -1:  # crime
            if recruits:
                recruits -= 1  # one officer investigates crime
            else:
                untreated += 1  # no officer available, crime untreated

        else:  # recruit officers
            recruits += e

    return untreated

print(problem427A())