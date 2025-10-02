from itertools import combinations

w, p = map(int, input().split(" "))
partitions = list(map(int, input().split(" ")))
partitions.append(0)
partitions.append(w)
widths = set()

for left, right in combinations(partitions, 2):
    widths.add(abs(right - left))

for w in sorted(widths)[:-1]:
    print(w, end=" ")
print(max(widths))
