def problem734A() -> str:
    _ = input()  # length of string of games played
    games = input()
    anton, danik = 0, 0

    for game in games:  # count number of games that Anton and Danik won
        if game == "A":
            anton += 1
        else:
            danik += 1
    
    if anton > danik:
        return "Anton"
    elif anton < danik:
        return "Danik"
    elif anton == danik:
        return "Friendship"

if __name__ == "__main__":
    print(problem734A())