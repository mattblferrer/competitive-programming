def problem1060A() -> int:
    n = int(input())  # number of cards
    cards = input()  # input cards as a string
    eights = 0
    non_eights = 0 
    for card in cards:  # get counts of 8s and non-8s in cards
        if card == "8":
            eights += 1
        else:
            non_eights += 1

    if eights > non_eights // 10:  # use excess 8s in last 10 digits
        return min(n // 11, eights, 
            ((eights - non_eights // 10) + non_eights) // 10)
    return eights

print(problem1060A())