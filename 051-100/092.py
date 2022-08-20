# function that will return 0 if the chain ends at 1 and return 1 if the chain ends at 89
def number_chain(num):
    temp = num
    while True:
        if num_ends[num] == 0:
            num_ends[temp] = 0
            return 0
        elif num_ends[num] == 1:
            num_ends[temp] = 1
            return 1
        else:
            square_sum = 0
            # get digits of num and add their squares to square_sum
            while num:
                digit = num % 10
                square_sum += digit * digit
                num //= 10
            num = square_sum


# given parameter
n = 10000000
num_ends = [-1]*n  # initialize to -1, meaning not processed
num_ends[1] = 0
num_ends[89] = 1

# output variable
startNums = 0

# iterate from 1 to n
for i in range(1, n):
    startNums += number_chain(i)

# print result
print(startNums)
