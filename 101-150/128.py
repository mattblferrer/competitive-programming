def hexagonal_neighbors(n: int, hex: int) -> list[int]:
    """returns the neighbors of n in a hexagonal counterclockwise spiral

    parameters: 
    n -- center number
    hex -- smallest hexagonal number larger than n"""
    ...


def hexagonal(index: int) -> int:
    """generate hexagonal number of certain index"""
    return index * (2 * index - 1)


def main():
    # declare variables
    limit = 2_000

    # print result
    print(f"The {limit}th tile in this sequence is {...}")


if __name__ == "__main__":
    main()
