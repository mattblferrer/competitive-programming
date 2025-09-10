# Blum Blum Shub algorithm
s = 290797  # s0
bbs = []
lines = 5000  # number of line segments

for i in range(lines):
    currLine = []

    for j in range(2):  # for each line segment
        currPoint = []

        for k in range(2):  # for each point
            s = (s*s) % 50515093
            t = s % 500
            currPoint.append(t)

        currLine.append(tuple(currPoint))
    bbs.append(currLine)

# algorithm
intersections = set()
# TODO algorithm

# print result
print("Intersections:", len(intersections))
