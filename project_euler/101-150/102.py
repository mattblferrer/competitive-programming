"""
This uses the barycentric coordinate system to determine if a point is inside
the triangle. 
"""


# read file
file1 = open('p102_triangles.txt', 'r')
lines = file1.readlines()

# declare variables
triangles = 0

# main loop
for line in lines:
    # remove whitespace, convert to ints
    line = [int(coord) for coord in line.strip().split(",")]  

    # barycentric coordinates
    x1, y1, x2, y2, x3, y3 = line

    a = ((y2-y3)*-x3 + (x3-x2)*-y3) / ((y2-y3)*(x1-x3) + (x3-x2)*(y1-y3))
    b = ((y3-y1)*-x3 + (x1-x3)*-y3) / ((y2-y3)*(x1-x3) + (x3-x2)*(y1-y3))
    c = 1 - a - b
    
    # check if origin is in triangle
    if 0 <= a <= 1 and 0 <= b <= 1 and 0 <= c <= 1:
        triangles += 1

# print result
print("Number of triangles for which the interior contains the origin:",
    triangles)
