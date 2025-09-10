def problem29B() -> float:
    l, d, v, g, r = map(int, input().split(' '))
    time_to_light = d / v
    time_from_light = (l - d) / v
    if time_to_light % (g + r) < g:  # light is still green
        wait = 0
    else:  # light is red
        wait = (g + r) - (time_to_light % (g + r))

    return time_to_light + wait + time_from_light

print(problem29B())