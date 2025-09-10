from itertools import product


# yields all the rolls of x dice with y sides and their total sum
def dice_generator(x: int, y: int) -> tuple:
    dice = product(range(1, y+1), repeat=x)
    for roll in dice:
        yield roll, sum(roll)
        

# declare variables
s = 0
pyr = [0]*37  # counter for Pyramidal Peter
cub = [0]*37  # counter for Cubic Colin
total_pyr, total_cub = 4**9, 6**6  # total number of rolls

# Pyramidal Peter
for roll in dice_generator(9, 4):
    pyr[roll[1]] += 1

# Cubic Colin
for roll in dice_generator(6, 6):
    cub[roll[1]] += 1

# get probabilities for each possible roll
for i, roll in enumerate(pyr):
    s += (roll / total_pyr) * (sum(cub[:i]) / total_cub)

# print result 
print(round(s, 7))
