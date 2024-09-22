def Problem112A():  
    str1 = input().lower()
    str2 = input().lower()

    for char1, char2 in zip(str1, str2):
        if char1 < char2:
            return -1
        elif char1 > char2:
            return 1
        
    return 0

if __name__ == "__main__":
    print(Problem112A())
