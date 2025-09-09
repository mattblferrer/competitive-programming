def problem31A() -> None:
    n = int(input())
    a = list(map(int, input().split(' ')))
    
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                if a[i] + a[j] == a[k]:
                    print(k + 1, i + 1, j + 1)
                    return
                if a[i] + a[k] == a[j]:
                    print(j + 1, i + 1, k + 1)
                    return 
                if a[j] + a[k] == a[i]:
                    print(i + 1, j + 1, k + 1)
                    return
    
    print(-1)
    return

problem31A()