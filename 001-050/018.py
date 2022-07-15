"""
PLAN:
1. start at the bottom of the triangle
2. combine mini triangles into bigger triangles using the sum of the largest elements
3. "collapse" bottom row into the row directly above it
4. continue up the triangle

TRIANGLE:
75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
"""

total = 0
rows = 15  # number of rows of the triangle

print("Enter triangle: ")
triangle = [list(map(int, input().split())) for i in range(rows)]  # accept 2d array as input

# algorithm
currentRow = triangle[rows - 1]
for i in range(rows - 2, -1, -1):  # going up the triangle
    nextRow = [0 for j in range(i+1)]  # generate blank next row of length (row number + 1) 
    for j in range(i+1):
        if currentRow[j] > currentRow[j+1]:  # compare two terms directly adjacent and below
            nextRow[j] = triangle[i][j] + currentRow[j]  # if term down and to the left is greater
        else:
            nextRow[j] = triangle[i][j] + currentRow[j+1]  # if term down and to the right is greater
    print(nextRow)
    currentRow = nextRow
