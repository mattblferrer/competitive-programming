def problem1512A() -> None:
    test_cases = int(input())

    for _ in range(test_cases):
        _ = input()
        a = list(map(int, input().split(" ")))
        seen = {}

        for i, a_i in enumerate(a):  # find number that is seen more than once
            if a_i not in seen:
                seen[a_i] = [i]
            else:
                seen[a_i].append(i)
                if len(seen) > 1:  # check if spy seen
                    break   

        for i_list in seen.values():  # find spy in seen set
            if len(i_list) == 1:
                print(i_list[0] + 1)  # since 1-indexed

problem1512A()
        