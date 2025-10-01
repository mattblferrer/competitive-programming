n = int(input())
classlist = set(input().split(" "))
m = int(input())
attendance = set(input().split(" "))
 
a = len([i for i in classlist if i in attendance])
b = n-a
c = len([i for i in attendance if i not in classlist])
 
print(a)
print(b)
print(c)