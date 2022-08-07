# read file
file1 = open('p107_network.txt', 'r')
lines = file1.readlines()

# process lines
lineNum = 0
edges = []
initialWeight = 0

for line in lines:
    line = line.strip()  # strip whitespace
    lineArr = line.split(",")  # split into columns

    for i in range(lineNum):
        weight = lineArr[i]

        if weight != "-":
            lineArr[i] = int(lineArr[i])  # convert weights to int
            edges.append((lineArr[i], lineNum, i))  # convert edge weights to vertex form
            initialWeight += lineArr[i]

    lineNum += 1

# sort edges by weight
edges = sorted(edges)

# calculate MST using Prim's algorithm
usedVertices = {0}
finalWeight = 0

while True: 
    # main algorithm
    validEdges = []  # find valid edges
    for edge in edges:
        if edge[1] in usedVertices or edge[2] in usedVertices:  # valid edges
            # filter out edges that will form cycles
            if not (edge[1] in usedVertices and edge[2] in usedVertices):
                validEdges.append(edge)

    if validEdges:
        edge = min(validEdges)  # take minimum of valid edges
        finalWeight += edge[0]  # add weight of edge

        # add used vertices to total set
        usedVertices.add(edge[1])
        usedVertices.add(edge[2])

    else:
        break

# print result
print("Initial weight:", initialWeight)
print("Final weight:", finalWeight)
print("Weight saved:", initialWeight - finalWeight)
