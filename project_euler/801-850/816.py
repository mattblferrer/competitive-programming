def main(): 
    # declare variables
    s = 290797
    p_1 = s
    p_list = []
    points = 2_000_000
    min_distance = float('inf')

    # generate points using random generator and append to list
    for i in range(2 * points):
        s = s * s % 50_515_093

        if i % 2 == 1:
            p_list.append((p_1, p_2))
            p_1 = s
        else:
            p_2 = s


    # algorithm to find shortest distance between two points
    p_list = sorted(p_list)
    for idx, (p_1, p_2) in enumerate(p_list):
        # check closest 5 points in sorted list
        for q_1, q_2 in p_list[idx + 1:min(idx + 5, points)]:  
            # fast check for minimum distance
            diff_1, diff_2 = q_1 - p_1, q_2 - p_2
            if diff_1 > min_distance or diff_2 > min_distance:
                continue
            if -diff_1 > min_distance or -diff_2 > min_distance:
                continue

            # calculate precise distance using diagonal formula
            distance = ((q_1 - p_1) ** 2 + (q_2 - p_2) ** 2) ** 0.5

            if distance < min_distance:
                min_distance = distance

    # print result
    print(f"d({points}): {round(min_distance, 9)}")


if __name__ == "__main__":
    main()
