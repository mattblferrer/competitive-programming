import itertools
 
testcases = int(input())
substrings1 = [''.join(x) for x in itertools.product('ABCDEFGHIJKLMNOPQRSTUVWXYZ', repeat=1)]
substrings2 = [''.join(x) for x in itertools.product('ABCDEFGHIJKLMNOPQRSTUVWXYZ', repeat=2)]
substrings3 = [''.join(x) for x in itertools.product('ABCDEFGHIJKLMNOPQRSTUVWXYZ', repeat=3)]
substrings4 = [''.join(x) for x in itertools.product('ABCDEFGHIJKLMNOPQRSTUVWXYZ', repeat=4)]
substrings = substrings1+substrings2+substrings3+substrings4
 
for i in range(testcases):
    s = input()
    for j in substrings:
        if not s.__contains__(j):
            print(j)
            break