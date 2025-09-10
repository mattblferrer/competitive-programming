def problem381A() -> None:
    _ = input()  # number of cards on the table
    cards = list(map(int, input().split(" ")))
    s, d = 0, 0  # Sereja's and Dima's points
    left, right = 0, len(cards) - 1  # left, right pointers
    turn = 0  # 0 if Sereja's turn, 1 if Dima's 

    while left <= right:
        if cards[left] > cards[right]:  # take card from left
            if turn == 0: 
                s += cards[left]
            else:
                d += cards[left]
            left += 1
        
        else:  # take card from right
            if turn == 0: 
                s += cards[right]
            else:
                d += cards[right]
            right -= 1

        turn ^= 1  # pass turn to other player

    print(s, d)

problem381A()