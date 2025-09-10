calls = 1

def problem873D() -> list[int]: 
    def swap(l: int, r: int) -> None:
        global calls
        if l == r - 1:
            return 
        if calls < k:
            mid = (l + r) // 2
            arr[mid], arr[mid - 1] = arr[mid - 1], arr[mid]
            calls += 2
            swap(l, mid)
            swap(mid, r)
        else:
            return
        
    n, k = map(int, input().split())
    if k % 2 == 0:
        return [-1]
    
    arr = list(range(1, n + 1))
    swap(0, n)
    if calls == k:
        return arr
    return [-1]

print(*problem873D())