def problemF():
    n, m = map(int, input().split(" "))
    schools = []

    for _ in range(m):  # get list of teams
        t = int(input())
        schools.append(t)

    qualified = [0] * m
    q = 0  # number of teams qualified so far
    while True:
        for i, s in enumerate(schools):
            if s:
                qualified[i] += 1
                schools[i] -= 1
                q += 1
            if q == n:
                return qualified
        if sum(schools) == 0:
            return qualified

final_teams = problemF()
for x in final_teams:
    print(x)