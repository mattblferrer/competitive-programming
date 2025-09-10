# generates next row of Pascal's triangle from the previous row
def next_pascal_row(row: list[int]) -> list[int]:
    # add two adjacent elements together to create next in row
    output = [1] + [n + row[i+1] for i, n in enumerate(row[:len(row)-1])] + [1]

    return output


# returns True if the number n is squarefree, False otherwise
def is_squarefree(n: int) -> bool:
    for i in (2, 3):  # for 2 and 3
        if n % i == 0:  
            n //= i
            if n % i == 0:  # if divisible again
                return False

    for i in range(5, int(n**0.5)+2, 6):  # for 6k +- 1
        if i*i > n:
            break

        for j in (0, 2):
            if n % (i+j) == 0:
                n //= (i+j)
                if n % (i+j) == 0:
                    return False

    return True


def main():
    # declare variables
    rows = 50
    curr_row = [1]
    num_set = set()

    # generate Pascal's triangle rows
    for _ in range(rows):
        curr_row = next_pascal_row(curr_row)
        num_set = num_set.union(set(curr_row))

    # calculate squarefree sum
    squarefree_sum = sum(i for i in num_set if is_squarefree(i))

    # print result
    print(f"Sum of distinct squarefree numbers: {squarefree_sum}")


if __name__ == "__main__":
    main()
