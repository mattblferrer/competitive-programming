power = 7830457
factor = 28433
num = 1

for i in range(power):  # 2^power
    num *= 2
    num %= 10**10  # mod 10^10 to get the last 10 digits

num *= factor
num += 1
num %= 10**10  # last mod 10^10

print("The last 10 digits of this prime number are", num)
