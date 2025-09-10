def problem706B() -> None:
    n = int(input())
    x = sorted(map(int, input().split()))
    q = int(input())
    for _ in range(q):
        m_i = int(input())
        left, right = -1, n
        while right - left > 1:
            mid = (left + right) // 2
            if x[mid] > m_i:
                right = mid
            else:
                left = mid

        print(right)
        
problem706B()