from math import pi


def main():
    # declare initial variables
    h_i = 100  # initial height
    g = 9.81  # gravitational constant
    v_i = 20  # initial velocity

    # derive highest height and time to reach ground
    h = h_i + v_i * v_i / g - 0.5 * g * (v_i / g)**2  # highest height 
    t = (2 * h // g) ** 0.5  # time to reach ground
    print(h, t)


if __name__ == "__main__":
    main()
