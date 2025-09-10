# Enter your code here. Read input from STDIN. Print output to STDOUT
n, m = map(int, input().split(" "))

for i in range(1, n // 2 + 1):
    border = (m - (6 * i - 3)) // 2
    print("-" * border + (2 * i - 1) * ".|." + "-" * border)
    
print("-" * ((m - 7) // 2) + "WELCOME" + "-" * ((m - 7) // 2))
    
for i in range(n // 2, 0, -1):
    border = (m - (6 * i - 3)) // 2
    print("-" * border + (2 * i - 1) * ".|." + "-" * border)
