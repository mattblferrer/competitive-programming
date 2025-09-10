# Enter your code here. Read input from STDIN. Print output to STDOUT
t = int(input())
for _ in range(t):
    s = input()
    print(s[::2], s[1::2])
