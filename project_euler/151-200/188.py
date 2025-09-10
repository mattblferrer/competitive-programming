# declare variables
a = 1777
b = 1855
mod = 100000000

# main loop
k = a

for i in range(1, b):
    # use built in pow function with mod
    k = pow(a, k, mod)  

# print result
print(k)
