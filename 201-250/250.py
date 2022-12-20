from collections import Counter


# get counts of each occurrence of x^x mod 250
remainders = [pow(i, i, 250) for i in range(1, 250251)]
print(Counter(remainders))
    
# TODO calculate number of subsets
