n, k = map(int, input().split(" "))
scores = list(map(int, input().split(" ")))
minscore = scores[k - 1]
output = 0

for i in range(n):
    if scores[i] >= minscore and scores[i] != 0:
        output += 1
 
print(output)