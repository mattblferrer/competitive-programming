def problem886A() -> str:
    arr = list(map(int, input().split(' ')))
    arr_sum = sum(arr)
    if arr_sum % 2 == 1:  # if odd, no way to split into two
        return "NO"

    for a in range(6):  # first student
        for b in range(a + 1, 6):  # second student
            for c in range(b + 1, 6):  # third student
                if arr[a] + arr[b] + arr[c] == arr_sum // 2:
                    return "YES"
                
    return "NO"

print(problem886A())