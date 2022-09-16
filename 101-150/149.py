"""
CODE FOR TESTING:
arr = [-2, 5, 3, 2, 9, -6, 5, 1, 3, 2, 7, 3, -1, 8, -4, 8]
print("Maximum sum subsequence:", highest_subsequence_2d(arr, 4))
"""


# returns the terms of a lagged fibonacci generator with n terms
def lagged_fib_gen(n: int) -> list[int]:
    i = 1
    terms = []

    while i <= n:  
        if i <= 55:  # terms 1 to 55
            term = (100003 - 200003*i + 300007*i*i*i) % 1000000 - 500000
        else:  # terms 56 to n
            term = (terms[i-25] + terms[i-56]) % 1000000 - 500000

        terms.append(term)
        i += 1

    return terms


# returns the highest subsequence sum in a 1-dimensional array
def highest_subsequence(arr: list[int]) -> int:
    maximum_sum = 0
    curr_sum = 0

    for value in arr:
        if curr_sum <= 0:
            curr_sum = value

        else:
            curr_sum += value

        # check if subsequence is highest for current row
        if maximum_sum < curr_sum:
            maximum_sum = curr_sum

    return maximum_sum


# returns the highest subsequence in the rows of an n x n grid
def max_rows(arr: list[int], n: int) -> int:
    maximum_sum = 0
    
    for row in range(n):
        row_seq = highest_subsequence(arr[row*n:row*n+n])
        if row_seq > maximum_sum:
            maximum_sum = row_seq

    return maximum_sum


# returns the highest subsequence in the columns of an n x n grid
def max_columns(arr: list[int], n: int) -> int:
    maximum_sum = 0
    
    for col in range(n):
        col_seq = highest_subsequence(arr[col:n*n:n])
        if col_seq > maximum_sum:
            maximum_sum = col_seq

    return maximum_sum


# returns the highest subsequence in the diagonals of an n x n grid
def max_diags(arr: list[int], n: int) -> int:
    maximum_sum = 0
    
    for d in range(n):
        # upper right half of grid
        seq1 = highest_subsequence(arr[d:n*(n-d):n+1])
        # lower left half of grid
        seq2 = highest_subsequence(arr[d*n:n*n:n+1])

        maximum_sum = max(seq1, seq2, maximum_sum)

    return maximum_sum


# returns the highest subsequence in the antidiagonals of an n x n grid
def max_adiags(arr: list[int], n: int) -> int:
    maximum_sum = 0
    
    for d in range(n):
        # upper left half of grid
        seq1 = highest_subsequence(arr[d:n*d+1:n-1])
        # lower right half of grid
        seq2 = highest_subsequence(arr[n*(d+2)-1:n*n:n-1])

        maximum_sum = max(seq1, seq2, maximum_sum)

    return maximum_sum


# returns the highest subsequence in a 2D grid (n x n)
def highest_subsequence_2d(arr: list[int], n: int) -> int:
    funcs = [max_rows, max_columns, max_diags, max_adiags]

    return max(func(arr, n) for func in funcs)

# print result
print("Maximum sum subsequence:", highest_subsequence_2d(lagged_fib_gen(4000000), 2000))
