def problem467B() -> int:
    _, m, k = map(int, input().split(' '))
    players = []

    for _ in range(m):  # get other players as input
        player = int(input())
        players.append(player)
    fedor = int(input())  # since Fedor is the (m + 1)th or last player
    
    friends = 0
    for player in players:
        if (fedor ^ player).bit_count() <= k:
            friends += 1
    
    return friends

print(problem467B())