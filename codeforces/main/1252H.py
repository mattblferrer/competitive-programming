def problem1252H() -> str:
    n = int(input())
    lands = []
    for _ in range(n):  # l_i <= w_i for all l_i, w_i
        l_i, w_i = map(int, input().split(' '))
        lands.append((min(l_i, w_i), max(l_i, w_i)))

    lands.sort(reverse=True)  # biggest to smallest length, then width
    max_area = max(lands[i][0] * lands[i][1] for i in range(n)) 
    curr_max = 0

    for i in range(1, n):  # get largest w_j for each j < i
        if lands[i - 1][1] > curr_max:
            curr_max = lands[i - 1][1]

        # store twice area to avoid floating-point errors
        curr_area = lands[i][0] * min(lands[i][1], curr_max) * 2  
        max_area = max(max_area, curr_area)
        
    if max_area % 2 == 0:  # convert twice area to correct decimal repr
        return f"{max_area // 2}.0"
    return f"{max_area // 2}.5" 

print(problem1252H())