def problem268A() -> int:
    n = int(input())  # number of teams
    home = []  # colors of home uniforms
    guest = []  # colors of guest uniforms

    for _ in range(n):  # get input of home, guest uniform colors
        h, g = input().split(" ")
        home.append(h)
        guest.append(g)

    same_colors = 0
    for h in home:  # count number of times home uniform = guest uniform
        for g in guest:
            if h == g:
                same_colors += 1

    return same_colors

print(problem268A())