def problem110A() -> str:
    n = input()
    lucky = 0 

    for digit in n:  # count lucky digits in n
        if digit == "4" or digit == "7":
            lucky += 1
    
    if lucky == 4 or lucky == 7:  # is nearly lucky number
        return "YES"
    return "NO"

print(problem110A())