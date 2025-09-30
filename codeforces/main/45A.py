def problem45A() -> str:
    months = ["January", "February", "March", "April", "May", "June", 
              "July", "August", "September", "October", "November", "December"]
    s = input()
    k = int(input())
    curr = months.index(s)
    return months[(curr + k) % 12]

print(problem45A())