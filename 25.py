digitLimit = 1000
a, b = 1, 1
ctr = 2  # index of term b

while b < 10**(digitLimit-1):  # 10^(digitLimit-1)is the first number to have (digitLimit) digits
    a, b = b, a+b
    ctr += 1

print(ctr)
