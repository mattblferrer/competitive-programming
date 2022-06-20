limit = 1000 # given parameter
output = 0

for i in range(1, limit+1):
    output += i**i

print("Power sum: " + str(output))
