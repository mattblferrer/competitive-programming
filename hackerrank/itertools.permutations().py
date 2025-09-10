# Enter your code here. Read input from STDIN. Print output to STDOUT
from itertools import permutations


s, k = input().split(" ")
for perm in sorted(permutations(s, int(k))):
    print("".join(perm))
