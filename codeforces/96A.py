def problem96A() -> str:
    players = input()
    previous = ""
    consecutive = 0
    
    for player in players:
        if player == previous:
            consecutive += 1
        else:
            consecutive = 1
        previous = player
        if consecutive == 7:
            return "YES"

    return "NO"

print(problem96A())