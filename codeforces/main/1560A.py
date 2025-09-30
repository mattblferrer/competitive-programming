def problem1560A() -> None:
    test_cases = int(input())
    sequence = []
    k = 0  # starting element to generate sequence

    while len(sequence) < 1000:  # generate sequence
        k += 1
        if k % 3 == 0 or k % 10 == 3:
            continue
        sequence.append(k)

    for _ in range(test_cases):
        k = int(input())
        print(sequence[k - 1])  # since 1-indexed

problem1560A()