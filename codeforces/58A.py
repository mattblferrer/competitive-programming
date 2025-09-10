def problem58A() -> str:
    string = input()
    hello_ptr = 0
    hello = "hello"

    for char in string:
        if char == hello[hello_ptr]:
            hello_ptr += 1
        if hello_ptr == 5:
            return "YES"
    return "NO"

print(problem58A())