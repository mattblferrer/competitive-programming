# returns True if x+y, x-y, x+z, x-z, y+z, and y-z are all squares
def perfect_square_collection(x: int, y: int, z: int) -> bool:
    collection = (x+z, x-z, y+z)

    for i in collection:
        if i not in squares:
            return False
    return True


# returns the lowest perfect square collection (x, y, z)
def find_perfect_sqr_collection() -> tuple[int]:
    for xy_sum in square_iter:  # x+y
        # iterate through x-y, x-y != 0
        for xy_diff in square_iter[(xy_sum % 2)+1::2]:  
            if xy_diff >= xy_sum // 2:
                break
            
            x = (xy_sum + xy_diff) // 2
            y = xy_sum - x
            
            # selecting z
            for yz_diff in square_iter:
                if yz_diff > y:
                    break
                    
                z = y - yz_diff
                if perfect_square_collection(x, y, z):
                    return x, y, z

        print(xy_sum)  # progress tracker


# loop through squares
square_iter = [i*i for i in range(1, 2000)]  # 2,000 is a guess limit
squares = set(square_iter)  # convert to set for faster square checking

# print result
answer = find_perfect_sqr_collection()
print(f"(x, y, z): {answer}, sum: {sum(answer)}")
