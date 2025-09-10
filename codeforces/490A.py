def problem490A() -> None:
    _ = input()  # number of students
    students = list(map(int, input().split(" ")))
    subjects = {
        1: [],  # good at programming
        2: [],  # good at maths
        3: [],  # good at PE
    }

    for i, s in enumerate(students, start=1):  # 1-indexed students
        subjects[s].append(i)

    min_length = min(len(s_list) for s_list in subjects.values())
    print(min_length)  # number of triplets that can be formed
    for i in range(min_length):
        for j in range(1, 4):
            print(subjects[j][i], end=" ")
        print("")

problem490A()