# declare variables
x0, y0 = 0.0, 10.1  # starting point
x1, y1 = 1.4, -9.6  # next point

# calculate reflection beams
beams = 0

while True:
    m = (y1-y0)/(x1-x0)
    tan = -4*x1/y1  # slope of tangent line
    norm = y1/(4*x1)  # slope of normal line
    
    # TODO calculate next point where the beam hits the ellipse
    x0, y0 = x1, y1
    print(x0, y0, x1, y1)

    # check if beam went out of the ellipse
    if abs(x1) < 0.01:
        break
    beams += 1  # calculate next beam

# print result
print(beams)
