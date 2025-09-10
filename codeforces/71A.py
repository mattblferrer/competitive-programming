def problem71A() -> None:
    lines = int(input())

    for i in range(lines):
        word = input()
        if len(word) > 10:
            print(word[:1] + str(len(word) - 2) + word[-1])
        else: 
            print(word)

problem71A()