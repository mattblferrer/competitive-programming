def problem43A() -> str:
    n = int(input())
    scores = {}

    for _ in range(n):
        team = input()
        if team not in scores:
            scores[team] = 1
        else:
            scores[team] += 1
    
    maximum_score = max(scores.values())
    for team, score in scores.items():
        if score == maximum_score:
            return team

print(problem43A())