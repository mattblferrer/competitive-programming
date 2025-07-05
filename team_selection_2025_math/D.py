from math import gcd

def problemD():
    x_b, y_b = map(int, input().split())
    x_1, y_1, x_2, y_2 = map(int, input().split())

    g = gcd(x_b, y_b)
    s_x = x_b // g
    s_y = y_b // g
    if g == 1:
        print("Yes")
        return

    x_lo = min(x_1, x_2)
    x_hi = max(x_1, x_2)
    y_lo = min(y_1, y_2)
    y_hi = max(y_1, y_2)

    if s_x < x_lo or s_y < y_lo or s_x > x_hi or s_y > y_hi:
        print("No")
        print(s_x, s_y)
        return
    
    next_xr = x_hi - x_hi % s_x + s_x
    next_yr = next_xr * s_y // s_x
    next_yu = y_hi - y_hi % s_y + s_y
    next_xu = next_yu * s_x // s_y
    close_x = min(next_xr, next_xu)
    close_y = min(next_yr, next_yu)
    if close_x >= x_b:
        print("Yes")
        return
    print("No")
    print(close_x, close_y)

problemD()