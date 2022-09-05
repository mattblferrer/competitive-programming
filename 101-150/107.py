# read file
file1 = open('p107_network.txt', 'r')
lines = file1.readlines()

# process lines and calculate initial weight
edges = []
initialWeight = 0

for lineNum, line in enumerate(lines):
    line = line.strip().split(",")  # strip whitespace and split into columns

    for i, weight in enumerate(line[:lineNum]):
        if weight != "-":
            line[i] = int(weight)  # convert weights to int
            edges.append((line[i], lineNum, i))  # convert edge weights to vertex form
            initialWeight += line[i]

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
print(f"Initial weight: {initialWeight}")
print(f"Final weight: {finalWeight}")
print(f"Weight saved: {initialWeight - finalWeight}")
