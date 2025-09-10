def problem208A() -> str:
    words = input().split("WUB")
    string = ""
    for word in words:
        if word != "":
            string += word + " "
            
    return string.rstrip()
 
print(problem208A())