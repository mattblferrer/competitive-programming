problems = int(input())
solved = 0

for i in range(problems):
    scores = input()
    scorelist = scores.split(" ")
    sum = 0
    for j in scorelist:
        if int(j):
            sum += 1
    if sum > 1:
        solved += 1
        
print(solved)