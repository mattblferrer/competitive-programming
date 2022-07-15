# returns if a number n is divisible by 3 or 5 
def divisible(n):
    if n % 3 == 0:
        return True
    if n % 5 == 0:
        return True
    return False


# main loop
output = 0

for i in range(1, 1000):
    if divisible(i):
        output += i

print(output)
