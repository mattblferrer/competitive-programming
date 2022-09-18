from math import inf


# Dijkstra's algorithm for a grid of size x_size by y_size
def dijkstra_grid(xs: int, ys: int, x_size: int, y_size: int, grid: list) -> list:
    # converts neighbor numeric code to (x, y) form
    def convert_neighbor(x: int, y: int, neighbor: int) -> tuple:
        # convert neighbor code to node
        if neighbor == 0:
            x1, y1 = (x, y-1) if y > 0 else (x, 0)
        elif neighbor == 1:
            x1, y1 = (x+1, y) if x < x_size-1 else (x_size-1, y)
        elif neighbor == 2:
            x1, y1 = (x, y+1) if y < y_size-1 else (x, y_size-1)
        elif neighbor == 3:
            x1, y1 = (x-1, y) if x > 0 else (0, y)

        return x1, y1


    # updates the tentative distance between all neighbors of a node (x, y)
    def calc_neighbors_grid(x: int, y: int, neighbors: list) -> list:
        # iterate through all neighbors and calculate distance
        for x1, y1 in neighbors:
            # update distance array based on node
            current_distance = distance[y1][x1]
            new_distance = distance[y][x] + grid[y1][x1]
            distance[y1][x1] = min(current_distance, new_distance)

        unvisited_set.remove((x, y))
        return distance


    # generate all points (x, y) in unvisited set
    def generate_unvisited_set() -> list:
        unvisited_set = set()

        for x in range(x_size):  
            for y in range(y_size):
                if not visited[y][x]:
                    unvisited_set.add((x, y))

        return unvisited_set


    # initialize visited and unvisited sets
    visited = [[False for _ in row] for row in rows]
    unvisited_set = generate_unvisited_set()
    neighbor_code = [0, 1, 2]  # kwise from top (0, 1, 2, 3)
    destination = (79, 79)
            
    # tentative distance array for nodes (x, y)
    x, y = (xs, ys)  # initial node
    distance = [[inf for _ in range(y_size)] for _ in range(x_size)]
    distance[y][x] = grid[y][x]

    # pathfinding algorithm
    while destination in unvisited_set:
        # update distances to neighbors from unvisited node
        neighbors = [convert_neighbor(x, y, n) for n in neighbor_code]
        distance = calc_neighbors_grid(x, y, neighbors)

        # search for nearest neighbors still in unvisited set
        minimum_dist = inf
        for node in unvisited_set:
            if distance[node[1]][node[0]] < minimum_dist:
                minimum_dist = distance[node[1]][node[0]]
                minimum_node = node

        x, y = minimum_node

    return distance



# read from file
with open("p082_matrix.txt", "r") as f:
    lines = f.readlines()

# strip whitespace and format into 2D array
rows = []
for row in lines:
    row = list(map(int, row.strip().split(",")))
    rows.append(row)

# declare variables
x_start = y_start = 0  # starting coordinates
x_size = y_size = 80  # size of grid

# calculate distances from each point in left column and get minimum
minimum_dist = inf

while y_start < y_size:
    grid = dijkstra_grid(x_start, y_start, x_size, y_size, rows)
    min_grid = min(grid[i][79] for i in range(y_size))

    if min_grid < minimum_dist:  # compare minimum distances
        minimum_dist = min_grid

    print(y_start)  # progress tracker
    y_start += 1

# print result
print(minimum_dist)
