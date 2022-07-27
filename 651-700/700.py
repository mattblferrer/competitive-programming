"""
The GCD of 1504170715041707 and 4503599627370517 is 1, so they must have a 
modular multiplicative inverse.
"""


# returns the modular multiplicative inverse of num mod x
def mod_mult_inv(num, x):
    r0, r1 = x, num
    t0, t1 = 0, 1

    # extended Euclidean algorithm
    while r1 != 0:
        q = r0 // r1
        r0, r1 = r1, r0 % r1  # remainders after Euclidean division
        t0, t1 = t1, (t0 - t1*q) % x
        
    return t0
        

# declare variables
a = 1504170715041707
m = 4503599627370517
coin = 1504170715041707  # starting Eulercoin
maximum = 1504170715041707
eulercoinSum = 1504170715041707

# find first Eulercoins
for i in range(1, 42298634):  # 42298634 found through brute force search
    coin += a
    if coin >= m:
        coin -= m

    if maximum > coin:
        maximum = coin
        eulercoinSum += coin

# find modular multiplicative inverse
inv = mod_mult_inv(a, m)

# calculate later Eulercoins
coin = 0
minimum = m

for i in range(1, maximum):
    coin += inv
    if coin >= m:
        coin -= m
    
    if minimum > coin:
        minimum = coin 
        eulercoinSum += i

# print result
print("The sum of all Eulercoins is", eulercoinSum)
