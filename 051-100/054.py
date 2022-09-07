"""
These functions check which hands satisfy certain criteria (i.e. royal flush, four of a kind, etc.)
They take two inputs: player 1 and player 2's card numbers (n), and their suits (s)
"""
from collections import Counter


def royal_flush(n: list, s: list) -> list:
    winners = []

    # check hands
    for player in range(1, 3):
        is_straight = True
        is_flush = True
        is_royal = True

        for index in range(4):
            # check if royal
            if max(n[player]) != 14:
                is_royal = False

            # check if straight
            difference = sorted(n[player])[index + 1] - sorted(n[player])[index]
            if difference != 1:
                is_straight = False

        # check if flush
        if len(set(s[player])) != 1:
            is_flush = False

        if is_straight and is_flush and is_royal:
            winners.append(player)

    return winners


def straight_flush(n: list, s: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        is_straight = True
        is_flush = True

        # check if straight
        for index in range(4):
            difference = sorted(n[player])[index + 1] - sorted(n[player])[index]
            if difference != 1:
                is_straight = False

        # check if flush
        if len(set(s[player])) != 1:
            is_flush = False

        if is_straight and is_flush:
            # maximum
            highest[player-1] = max(n[player])

            winners.append(player)

    return winners, highest


def four_kind(n: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts how frequent numbers are in the hand
        for key in freqs:
            if freqs[key] == 4:
                # maximum
                highest[player - 1] = key

                winners.append(player)

    return winners, highest


def full_house(n: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts how frequent numbers are in the hand

        # count how many pairs and threes there are
        pairs = 0
        threes = 0
        for key in freqs:
            if freqs[key] == 2:
                pairs += 1
            if freqs[key] == 3:
                threes += 1

            # maximum
            if highest[player-1] < key:
                highest[player-1] = key

        if pairs == 1 and threes == 1:  # full house check
            winners.append(player)

    return winners, highest


def flush(n: list, s: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        if len(set(s[player])) == 1:  # if suit is the same across the list
            # maximum
            highest[player - 1] = max(n[player])

            winners.append(player)

    return winners, highest


def straight(n: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        is_straight = True
        for index in range(4):
            difference = sorted(n[player])[index + 1] - sorted(n[player])[index]
            if difference != 1:
                is_straight = False

        if is_straight:
            # maximum
            highest[player-1] = max(n[player])

            winners.append(player)

    return winners, highest


def three_kind(n: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts how frequent numbers are in the hand
        for key in freqs:
            if freqs[key] == 3:
                # maximum
                highest[player - 1] = key

                winners.append(player)

    return winners, highest


def two_pairs(n: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts how frequent numbers are in the hand

        # count how many pairs there are
        pairs = 0
        for key in freqs:
            if freqs[key] == 2:
                pairs += 1

                # compare with maximum
                if highest[player-1] < key:
                    highest[player-1] = key

        if pairs == 2:
            winners.append(player)

    return winners, highest


def one_pair(n: list) -> tuple:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts how frequent numbers are in the hand

        for key in freqs:
            if freqs[key] == 2:
                winners.append(player)
                highest[player-1] = key

    return winners, highest


# returns the player with the highest hand
def highest_hand(n: list, highest: list) -> int:
    # compare highest of hands
    if highest[0] > highest[1]:
        return 1
    elif highest[1] > highest[0]:
        return 2

    # if highest cards are the same, sort hands and compare next best
    hand_1 = sorted(n[1])
    hand_2 = sorted(n[2])

    # comparison
    for i in range(4, -1, -1):
        if hand_1[i] > hand_2[i]:
            return 1
        elif hand_2[i] > hand_1[i]:
            return 2


# check player 1 and player 2's hands and determine who wins
def hands_check(n: list, s: list) -> int:
    # royal flush
    result = royal_flush(n, s)
    if result:
        return result

    # for all other combinations of hands
    funcList = [straight_flush(n, s), four_kind(n), full_house(n), flush(n, s),
        straight(n), three_kind(n), two_pairs(n), one_pair(n)]

    for func in funcList:
        result = func  # run function to check for each hand

        if result[0] == [1, 2]:
            return highest_hand(n, result[1])
        elif result[0]:
            return result[0][0]

    # highest hand
    return highest_hand(n, [0, 0])


# read from poker.txt
file1 = open('p054_poker.txt', 'r')
lines = file1.readlines()
lines = [line.rstrip() for line in lines]  # strip \n from line

# declare variables
player_wins = [0, 0]  # for player 1, 2

# read player 1 and player 2 hands from lines
for i in range(1000):
    # read lines from list into string
    line = lines[i].split(" ")

    # split into card number and suits
    nums = []
    suits = []
    num_dict = {"T": 10, "J": 11, "Q": 12, "K": 13, "A": 14}  # mapping of cards

    for card in line:
        # filter nums and remove letters for easier comparisons
        num = card[0]

        # match letter cards to number equivalent
        if num_dict.get(num) is not None:  
            num = num_dict.get(num)

        nums.append(int(num))

        # add cards' suit
        suits.append(card[1])

    # read hands from list, 5 cards at a time
    num_dict = {
        1: nums[0:5],  # first half of line to player 1
        2: nums[5:10]  # second half of line to player 2
    }
    suits_dict = {
        1: suits[0:5],
        2: suits[5:10]
    }

    # check for hands
    winner = hands_check(num_dict, suits_dict)

    # count number of wins for each player
    player_wins[winner - 1] += 1

# print result
print(f"Player 1 wins: {player_wins[0]}")
print(f"Player 2 wins: {player_wins[1]}")
