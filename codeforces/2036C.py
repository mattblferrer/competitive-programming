def problem2036C() -> None:
    test_cases = int(input())

    for _ in range(test_cases):
        s = list(map(int, input()))
        q = int(input())
        occurrences = set()

        # get initial set of all i where s[i:i + 4] == '1100'
        for i in range(len(s) - 3):
            if s[i] == 1 and s[i + 1] == 1 and s[i + 2] == 0 and s[i + 3] == 0:
                occurrences.add(i + 1)

        # get queries i, v and change s[i] to v
        for _ in range(q):
            i, v = map(int, input().split(' '))
            s[i - 1] = v

            # base case: if s is shorter than 1100, automatically NO
            if len(s) < 4:
                print("NO")
                continue

            # when s[i] changed, all s[k] from i - 4 to i + 4 might be affected
            for k in range(i - 4, i + 5):
                if not (0 < k < len(s) - 2):  # make sure k is in bounds
                    continue
                if s[k - 1] and s[k] and not s[k + 1] and not s[k + 2]:  # 1100
                    occurrences.add(k)
                else:
                    if k in occurrences:  # remove if not 1100 anymore
                        occurrences.remove(k)
                    
            # check if 1100 still occurs in string s
            if len(occurrences):
                print("YES")
            else:
                print("NO")

problem2036C()