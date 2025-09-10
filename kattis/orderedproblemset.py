n = int(input())
diffs = []  # list of difficulties of the problems
possible_k = []

for _ in range(n):
    diff = int(input())
    diffs.append(diff)

for k in range(2, n + 1):
    if n % k != 0:
        continue

    # partition into groups
    partitions = []
    p = []  # current partition
    ctr = 0
    for diff in diffs:  
        if ctr == n // k:
            partitions.append(p)
            p = [diff]
            ctr = 1
        else:
            p.append(diff)
            ctr += 1
    partitions.append(p)  # append last partition to list

    # check if partition ordering condition applies
    for p1, p2 in zip(partitions, partitions[1:]):
        if max(p1) > min(p2):
            break
    else:
        possible_k.append(k)

if possible_k:
    for k in possible_k:
        print(k)
else:
    print(-1)
