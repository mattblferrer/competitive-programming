# Enter your code here. Read input from STDIN. Print output to STDOUT
happiness = 0
n, m = map(int, input().split(" "))
arr = list(map(int, input().split(" ")))
A = set(map(int, input().split(" ")))
B = set(map(int, input().split(" ")))

for i in arr:
    if i in A:
        happiness += 1
    if i in B:
        happiness -= 1
print(happiness)
