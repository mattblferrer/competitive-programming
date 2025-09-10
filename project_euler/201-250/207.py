# declare variables
limit = 12345
ratio = 1
exp = 2

# search for first power of 2 with P(m) < 1/12345
while ratio < limit:
    exp += 1
    ratio = (2 ** exp - 1) / exp

# refine search to find smallest number of partitions, P(m) < 1/12345
for i in range(2 ** (exp - 1), 2 ** exp):
    ratio = i / (exp - 1)
    if ratio > limit:
        break

answer = i * (i + 1)  # find m from number of partitions
    
# print result
print(f"The smallest m for which P(m) = 1/{limit} = {answer}")
