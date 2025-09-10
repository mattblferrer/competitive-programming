def problem2A() -> str:
    n = int(input())
    rounds = []
    scores = {}

    # find list of people with maximum score
    for _ in range(n):
        name, score = input().split()
        score = int(score)
        rounds.append((name, score))
        if name in scores:
            scores[name] += score
        else:
            scores[name] = score

    maximum_score = max(scores.values())
    winners = set()
    for name, score in scores.items():
        if score == maximum_score:
            winners.add(name)

    # find first player from winners to get a score at or above the maximum
    scores = {w:0 for w in winners}
    for name, score in rounds:
        if name in scores:
            scores[name] += score  
            if scores[name] >= maximum_score:
                return name

print(problem2A())