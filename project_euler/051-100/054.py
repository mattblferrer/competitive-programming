"""
These functions check which hands satisfy certain criteria (i.e. royal flush, 
four of a kind, etc.)
They take two inputs: player 1 and player 2's card numbers (n), and 
their suits (s)
"""
from collections import Counter


def straight_check(n: list) -> bool:
    for index in range(4):
        if sorted(n)[index + 1] - sorted(n)[index] != 1:
            return False
    return True


def royal_flush(n: list, s: list) -> list:
    winners = []

    # check hands
    for player in range(1, 3):
        is_straight = straight_check(n[player])
        is_flush = len(set(s[player])) == 1
        is_royal = max(n[player]) == 14

        if is_straight and is_flush and is_royal:
            winners.append(player)

    return winners


def straight_flush(n: list, s: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        is_straight = straight_check(n[player])
        is_flush = len(set(s[player])) == 1

        if is_straight and is_flush:
            highest[player - 1] = max(n[player])  # maximum
            winners.append(player)

    return winners, highest


def four_kind(n: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts frequency of numbers in the hand

        if sorted(freqs.values()) == [4, 1]:  # four of a kind check
            highest[player - 1] = max(freqs)  # maximum
            winners.append(player)

    return winners, highest


def full_house(n: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts frequency of numbers in the hand
        
        if sorted(freqs.values()) == [2, 3]:  # full house check
            highest[player - 1] = max(freqs)  # maximum
            winners.append(player)

    return winners, highest


def flush(n: list, s: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        if len(set(s[player])) == 1:  # if suit is the same across the list
            highest[player - 1] = max(n[player])  # maximum
            winners.append(player)

    return winners, highest


def straight(n: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        if straight_check(n[player]):  # check if straight
            highest[player-1] = max(n[player])  # maximum
            winners.append(player)

    return winners, highest


def three_kind(n: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts frequency of numbers in the hand
        for key in freqs:
            if freqs[key] == 3:
                highest[player - 1] = key  # maximum
                winners.append(player)

    return winners, highest


def two_pairs(n: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts frequency of numbers in the hand
        
        if sorted(freqs.values()) == [1, 2, 2]:  # full house check
            highest[player - 1] = max(freqs)  # maximum
            winners.append(player)

    return winners, highest


def one_pair(n: list) -> tuple[list, list[int]]:
    winners = []
    highest = [0, 0]

    # check hands
    for player in range(1, 3):
        freqs = Counter(n[player])  # counts frequency of numbers in the hand
        
        for key, value in freqs.items():
            if value == 2:
                highest[player - 1] = key  # maximum
                winners.append(player)

    return winners, highest


# returns the player with the highest hand
def highest_hand(n: list, highest: list) -> int:
    # compare highest of hands
    if highest[0] > highest[1]:
        return 1
    elif highest[1] > highest[0]:
        return 2

    # if highest cards are the same, sort hands and compare next best
    hand_1 = sorted(n[1],reverse=True)
    hand_2 = sorted(n[2],reverse=True)

    # comparison
    for card_1, card_2 in zip(hand_1, hand_2):
        if card_1 > card_2:
            return 1
        elif card_1 < card_2:
            return 2


# check player 1 and player 2's hands and determine who wins
def hands_check(n: list, s: list) -> int:
    # royal flush
    result = royal_flush(n, s)
    if result:
        return result

    # for all other combinations of hands
    func_list = [straight_flush(n, s), four_kind(n), full_house(n), flush(n, s),
        straight(n), three_kind(n), two_pairs(n), one_pair(n)]

    for func in func_list:
        result = func  # run function to check for each hand

        if result[0] == [1, 2]:
            return highest_hand(n, result[1])
        elif result[0]:
            return result[0][0]

    # highest hand
    return highest_hand(n, [0, 0])


def main():
    # read from poker.txt
    with open('p054_poker.txt', 'r') as f:
        lines = f.readlines()
    lines = [line.rstrip().split(" ") for line in lines]  # strip \n from line

    # declare variables
    player_wins = [0, 0]  # for player 1, 2

    # read player 1 and player 2 hands from lines
    for line in lines:
        # split into card number and suits
        nums = []
        suits = []
        num_dict = {"T": 10, "J": 11, "Q": 12, "K": 13, "A": 14}

        for card in line:
            # filter nums and remove letters for easier comparisons
            num = card[0]

            # match letter cards to number equivalent
            if num_dict.get(num) is not None:  
                num = num_dict.get(num)

            nums.append(int(num))
            suits.append(card[1])  # add cards' suit

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


if __name__ == "__main__":
    main()
