from functools import cache


def hexagonal_neighbor_diff(n: int, h_rings: list[int], h: int) -> list[int]:
    """returns the differences between n and the neighbors of n in a 
    hexagonal counterclockwise spiral

    parameters: 
    n -- center number
    h_rings -- list of 4 hex numbers from hex(i-2) to hex(i+1)
    where hex(i) is the hex or centered hexagonal number of i
    h -- index of hex number"""
    # calculate where n is based on coordinate system
    side_pos: int = (n - h_rings[1] - 1) % h  # how far along n is on side
    side_num: int = (n - h_rings[1] - 1) // h  # which side n is on
    is_corner: bool = side_pos == 0  # if n is on corner of ring

    # get 2 neighbors on the ring (left, right)
    if n == h_rings[1] + 1:  # if n is at the start of a ring
        neighbors = [n + 1, h_rings[2]]
    
    elif n == h_rings[2]:  # if n is at the end of a ring
        neighbors = [n - 1, h_rings[1] + 1]
    
    else:  # if n is in the middle of a ring
        neighbors = [n - 1, n + 1]

    # get inner neighbors
    h_inner_lowest: int = h_rings[0] + (h - 1) * side_num + side_pos

    if is_corner:  # 1 inner
        if 1 < n < 8:  # if in second ring
            neighbors.append(1)
        else:
            neighbors.append(h_inner_lowest + 1)

    else:  # 2 inner
        if n == h_rings[2]:  # if n is at the end of a ring
            neighbors.extend([h_rings[0] + 1, h_inner_lowest])
        else:
            neighbors.extend([h_inner_lowest, h_inner_lowest + 1])

    # get outer neighbors
    h_outer_lowest: int = h_rings[2] + (h + 1) * side_num + side_pos

    if is_corner:  # 3 outer
        if n == h_rings[1] + 1:  # if n is at the start of the ring
            neighbors.extend([h_outer_lowest + 1, h_outer_lowest + 2, 
                h_rings[3]])
        else:  # if n is at the other corners of the ring
            neighbors.extend([h_outer_lowest + i for i in range(3)])
    
    else:  # 2 outer
        neighbors.extend([h_outer_lowest + 1, h_outer_lowest + 2])

    return [i - n if i > n else n - i for i in neighbors]


def hex(index: int) -> int:
    """generate hex (centered hexagonal) number of certain index"""
    return 3 * index * (index + 1) + 1


@cache
def isprime(num: int) -> bool:
    """returns True if num is prime"""
    if num < 2:
        return False
    if num == 2 or num == 3:  # for 2 and 3
        return True
    if num % 2 == 0 or num % 3 == 0:  # for 2 and 3
        return False

    for i in range(5, int(num ** 0.5) + 1, 6):  # for 6k +- 1
        if num % i == 0 or num % (i + 2) == 0:
            return False
    return True


def main():
    # declare variables
    limit: int = 2_000
    primes: int = 1
    hex_index: int = 1  # ()'th hex number
    n: int = 2  # number to be checked
    h_list: list[int] = [0] + [hex(i) for i in range(hex_index - 1, 
        hex_index + 2)]

    # PD(n) = 3 if and only if n = hex or n = hex + 1
    while primes < limit: 
        # update hex number list if n gets too big
        if n > h_list[2]:
            hex_index += 1
            h_list.pop(0)
            h_list.append(hex(hex_index + 1))

        if n > h_list[1] + 1:
            n = hex(hex_index)

        # calculate PD(n)
        pd_n: int = 0  
        for i in hexagonal_neighbor_diff(n, h_list, hex_index):
            if isprime(i):
                pd_n += 1
            if pd_n == 3:
                primes += 1
                break
        n += 1

    # print result
    print(f"The {limit}th tile in this sequence is {n - 1}")


if __name__ == "__main__":
    main()
