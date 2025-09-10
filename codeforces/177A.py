def problem177A() -> int:
    n = int(input())
    matrix = [list(map(int, input().split())) for _ in range(n)]
    sum_main = sum(matrix[i][i] for i in range(n))
    sum_sec = sum(matrix[i][n - i - 1] for i in range(n))
    sum_row = sum(matrix[n // 2][i] for i in range(n))
    sum_col = sum(matrix[i][n // 2] for i in range(n))
    return sum_main + sum_sec + sum_row + sum_col - 3 * matrix[n // 2][n // 2]

print(problem177A())