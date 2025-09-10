# read from file names.txt
with open('p022_names.txt', 'r') as f:
    names = f.read()

names = sorted(names.replace('"', '').split(","))  # cleaning and sorting input
name_score = 0  # getting name scores

# iterate through sorted name list, converting to uppercase ASCII
for i, current_name in enumerate(names, start=1):  
    name_score += i*sum(ord(char) - 64 for char in current_name)

# print result
print(f"The total of all the name scores in the file is {name_score}")
