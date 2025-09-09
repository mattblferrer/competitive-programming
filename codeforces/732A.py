def problem732A() -> int:
    k, r = map(int, input().split(" "))
    shovels = 1  # number of shovels bought 
    cost = k
    while True:
        if cost % 10 == 0 or cost % 10 == r:  # check if no change left
            return shovels
        cost += k
        shovels += 1

print(problem732A())