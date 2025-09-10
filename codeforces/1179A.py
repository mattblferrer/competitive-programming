from collections import deque

def problem1179A() -> None:
    n, q = map(int, input().split(' '))
    a = deque(map(int, input().split(' ')))

    # find index of maximum element in deque
    maximum = -1
    for i, a_i in enumerate(a):
        if maximum < a_i:
            max_index = i
            maximum = a_i

    # simulate A, B deque operation until max_index
    simulate = []
    for _ in range(max_index):
        A, B = a.popleft(), a.popleft()
        simulate.append((A, B))

        if A > B:
            a.appendleft(A)
            a.append(B)
        else:  # A <= B
            a.appendleft(B)
            a.append(A)

    # accept queries
    for _ in range(q):
        m_j = int(input())
        if m_j <= max_index:
            print(*simulate[m_j - 1])
        else:
            print(maximum, a[(m_j - (max_index + 1)) % (n - 1) + 1])

problem1179A()