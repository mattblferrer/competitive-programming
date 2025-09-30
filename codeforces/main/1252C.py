def problem1252C() -> None:
    def generateIntervals(l: list[int]) -> dict[int, tuple[int, int]]:
        intervals = dict()
        prev = -1
        start = 0
        end = -1
        
        for k in l:
            if prev == k:
                end += 1
            else:
                for j in range(start, end + 1):
                    intervals[j] = (start, end)
                end += 1
                start = end
            prev = k

        for j in range(start, n):
            intervals[j] = (start, n - 1)

        return intervals

    n, q = map(int, input().split(' '))
    r = [i % 2 for i in list(map(int, input().split(' ')))]
    c = [i % 2 for i in list(map(int, input().split(' ')))]
    r_intervals = generateIntervals(r)
    c_intervals = generateIntervals(c)

    for _ in range(q):
        ra, ca, rb, cb = map(int, input().split(' '))
        row_start, row_end = r_intervals[ra - 1]
        col_start, col_end = c_intervals[ca - 1]

        if row_start <= rb - 1 <= row_end and col_start <= cb - 1 <= col_end:
            print("YES")
        else:
            print("NO")

problem1252C()