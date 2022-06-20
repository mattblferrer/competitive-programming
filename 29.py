# given parameters
a = 100
b = 100
powerList = set()  # with no repeats

# generate all powers a^b
for i in range(2, a+1):
    for j in range(2, b+1):
        powerList.add(i**j)

# final output
print("The number of distinct powers a^b with a =", a, "and b =", b, "is", len(powerList))
