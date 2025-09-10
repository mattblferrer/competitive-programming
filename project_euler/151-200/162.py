"""
We use the inclusion-exclusion principle to count the number of hexadecimal
numbers with the requirements given.

|0 or 1 or A| = |0| + |1| + |A| - |0 and 1| - |0 and A| - |1 and A| + 
|0 and 1 and A|

|0 and 1 and A| = |0 or 1 or A| - (|0| + |1| + |A| - |0 and 1| - |0 and A| - 
|1 and A|)

For n-digit hex numbers:
Total: 15*16^(n-1)

|0| = 15*16^(n-1) - 15^n
|1| = |A| = 15*16^(n-1) - 14*15^(n-1), excluding leading zero

|0 or 1| = |0 or A| = 15*16^(n-1) - 14^n
|1 or A| = 15*16^(n-1) - 13*14^(n-1)

|0 and 1| = |0 and A| = |0 or 1|/|0 or A| - |0| - |1|/|A| respectively
|1 and A| = |1 or A| - |1| - |A|

|0 or 1 or A| = 15*16^(n-1) - 12*13^(n-1)
"""


# declare variables
digits = 16
base = 16
totalSum = 0

# calculate all hexadecimal numbers with 0, 1, A
for n in range(1, digits+1):
    digitSum = 0  # for n digits

    # 0, 1, A
    num0 = 15*16**(n-1) - 15**n
    num1 = numA = 15*16**(n-1) - 14*15**(n-1)
    digitSum += num0 + num1 + numA

    # sets with two elements (01, 0A, 1A)
    digitSum -= (2*num0 + num1 + numA) - (2*(15*16**(n-1) - 14**n))  # 01, 0A
    digitSum -= num1 + numA - (15*16**(n-1) - 13*14**(n-1))  # 1A

    # all three elements
    num01A = 15*16**(n-1) - 13**n
    digitSum = num01A - digitSum

    # add to total
    totalSum += digitSum

# print result in hexadecimal
answer = str(hex(totalSum)[2:]).upper()
print("Number of hexadecimal numbers:", answer)
