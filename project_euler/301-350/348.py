from collections import defaultdict


def main():
    # declare variables
    d = defaultdict(int)  # to store frequencies of palindrome sums
    palindrome_sum = 0

    # brute force through a, b, a^3 + b^2 = palindrome
    for a in range(2, 2_000):  # guess limits
        for b in range(2, 50_000):
            s = a*a*a + b*b
            if str(s) == str(s)[::-1]:  # check for palindrome
                d[s] += 1
                if d[s] == 4:  # 4 occurrences 
                    print(s)
                    palindrome_sum += s

    # print result
    print(palindrome_sum)


if __name__ == "__main__":
    main()
