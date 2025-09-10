def problem316A() -> str:
    s = input()
    letters = set()
    question_marks = 0

    for char in s:
        if char == "?":
            question_marks += 1
        elif char.isdigit():
            continue
        else:
            letters.add(char)
        
    codes = 1
    for i in range(len(letters)):
        if i == 0 and s[0].isalpha():
            codes *= 9
        else:
            codes *= (10 - i)

    if s[0] == "?":
        return str(codes * 9) + "0" * (question_marks - 1)
    else:
        return str(codes) + "0" * question_marks

print(problem316A())