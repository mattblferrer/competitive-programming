def main():
    # read file
    with open('p107_network.txt', 'r') as f:
        lines = f.readlines()

    # process lines and calculate initial weight
    edges = []
    initialWeight = 0

    for lineNum, line in enumerate(lines):
        line = line.strip().split(",")  # strip whitespace and split into columns

        for i, weight in enumerate(line[:lineNum]):
            if weight != "-":
                line[i] = int(weight)  # convert weights to int
                edges.append((line[i], lineNum, i))  # convert edge weights
                initialWeight += line[i]

    # calculate MST using Prim's algorithm
    edges = sorted(edges)  # sort edges by weight
    usedVertices = {0}
    finalWeight = 0

    while True: 
        # find valid edges
        validEdges = [e for e in edges if (e[1] in usedVertices) ^ 
        (e[2] in usedVertices)]  

        if not validEdges:
            break
        edge = validEdges[0]  # take minimum of valid edges
        finalWeight += edge[0]  # add weight of edge

        # add used vertices to total set
        usedVertices.update({edge[1], edge[2]})

    # print result
    print(f"Initial weight: {initialWeight}")
    print(f"Final weight: {finalWeight}")
    print(f"Weight saved: {initialWeight - finalWeight}")


if __name__ == "__main__":
    main()
