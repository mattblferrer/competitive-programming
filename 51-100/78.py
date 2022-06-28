# number of partitions for numbers 0, 1
partition_arr = [0, 1]


# returns the number of ways to partition a number into a sum of positive integers
def partition_number(num):
    num2 = num  # store num for final evaluation

    if num == 1:  # 1 = 1
        return 1
    elif num < 1:  # no ways to partition non-positive integer
        return 0
    else:  # greater than 1
        counter = 0
        difference_array = []  # numbers to subtract from num
        difference = 0

        # numbers for Euler's pentagonal number theorem
        while num > 0:
            counter += 1

            if counter % 2 == 0:
                difference += counter//2
                num -= counter // 2

            else:
                difference += counter
                num -= counter

            difference_array.append(difference)

        num = num2  # reset num

        if sum(difference_array) > num:
            difference_array = difference_array[:-1]  # remove last element

    # evaluate partition number
    partitions = 0

    for i in range(len(difference_array)):
        if i % 4 < 2:
            partitions += partition_arr[num - difference_array[i]]
        else:
            partitions -= partition_arr[num - difference_array[i]]

    # return final partition number
    return partitions


# fill out partition array
i = 1
current_partition = 1

while current_partition % 1000000 != 0:
    i += 1

    current_partition = partition_number(i)
    partition_arr.append(current_partition)

# print result
print("The least value of n for which p(n) is divisible by 1 million is", i-1)  # offset for partition array
print("Value of number of partitions:", partition_arr[-1])
