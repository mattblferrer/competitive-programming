def ABC121B() -> int:
    N, _, C = map(int, input().split(' '))
    B = list(map(int, input().split(' ')))
    A = []
    valid_codes = 0

    for _ in range(N):
        A_i = list(map(int, input().split(' ')))
        A.append(A_i)

    for A_i in A:
        code_sum = C
        for A_ij, B_ij in zip(A_i, B):
            code_sum += A_ij * B_ij

        if code_sum > 0:
            valid_codes += 1

    return valid_codes

print(ABC121B())