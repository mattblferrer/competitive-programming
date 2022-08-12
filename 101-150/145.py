"""
For 10^n: if n is:
0 or 2 mod 4: 20*30^((n/2) - 1)
1 mod 4: 0
3 mod 4: 100*500^((n-3)/4)

CODE FOR CHECKING:
# returns True if the number is reversible, False otherwise
def is_reversible(num):
    rev = num + int(str(num)[::-1])
    for digit in str(rev):
        if digit in {"2", "4", "6", "8", "0"}:
            return False

    return True
"""


# declare variables
maxP = 9  # max power of 10
reversibles = 0  # number of reversible numbers

# main loop 
for i in range(1, maxP+1):
    if i % 2 == 0:  # 0 or 2 mod 4
        reversibles += 20*30**(i//2 - 1)
    elif i % 4 == 3:  # 3 mod 4
        reversibles += 100*500**((i-3)//4)

# print result
print("Number of reversibles:", reversibles)
