n, k = input().split(" ")
n = int(n)
k = int(k)
scores = input().split(" ")
minscore = scores[k - 1]
output = 0

for i in range(n):
    if int(scores[i]) >= int(minscore) and int(scores[i]) != 0:
        output = output + 1
 
print(output)