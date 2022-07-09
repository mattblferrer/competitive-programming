"""
These functions check which hands satisfy certain criteria (i.e. royal flush, four of a kind, etc.)
They take two inputs: player 1 and player 2's card numbers (n), and their suits (s)
"""
from collections import Counter


def royal_flush(n, s):
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


def straight_flush(n, s):
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


def four_kind(n):
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


def full_house(n):
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


def flush(n, s):
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        if len(set(s[player])) == 1:  # if suit is the same across the list
            # maximum
            highest[player - 1] = max(n[player])

            winners.append(player)

    return winners, highest


def straight(n):
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


def three_kind(n):
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


def two_pairs(n):
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


def one_pair(n):
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
def highest_hand(n, highest):
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
def hands_check(n, s):
    # royal flush
    result = royal_flush(n, s)
    if result:
        return result

    # straight flush
    result = straight_flush(n, s)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # four of a kind
    result = four_kind(n)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # full house
    result = full_house(n)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # flush
    result = flush(n, s)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # straight
    result = straight(n)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # three of a kind
    result = three_kind(n)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # two pairs
    result = two_pairs(n)
    if result[0] == [1, 2]:
        return highest_hand(n, result[1])
    elif result[0]:
        return result[0][0]

    # one pair
    result = one_pair(n)
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
p1_wins = 0
p2_wins = 0

# read player 1 and player 2 hands from lines
for i in range(1000):
    # read lines from list into string
    line = lines[i].split(" ")

    # split into card number and suits
    nums = []
    suits = []

    for card in line:
        # filter nums and remove letters for easier comparisons
        num = card[0]

        if num == "T":
            num = 10
        elif num == "J":
            num = 11
        elif num == "Q":
            num = 12
        elif num == "K":
            num = 13
        elif num == "A":
            num = 14
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
    if winner == 1:
        p1_wins += 1
    elif winner == 2:
        p2_wins += 1

# print result
print("Player 1 wins: {}".format(p1_wins))
print("Player 2 wins: {}".format(p2_wins))
