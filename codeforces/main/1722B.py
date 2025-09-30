def problem1722B() -> str:
    _ = input()  # length of strings
    string1 = input()
    string2 = input()

    for color1, color2 in zip(string1, string2):
        if color1 != color2:
            if color1 == "R" or color2 == "R":
                return "NO"
            
    return "YES"
 
test_cases = int(input())
for _ in range(test_cases):
    print(problem1722B())