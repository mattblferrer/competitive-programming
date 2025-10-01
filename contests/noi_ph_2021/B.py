testcases = int(input())
 
for i in range(testcases):
    a,b,c,d = map(int, input().split(" "))
 
    if c <= d:
        print("-1")
    else:
        growthPerDay = c-d
        heightDifference = b-a
        days = heightDifference/growthPerDay
        print(days)