def problem236A() -> str:
    name = input()
    distinct_chars = len(set(name))
    if distinct_chars % 2 == 0:  # female
        return "CHAT WITH HER!"
    return "IGNORE HIM!"  # male
        

if __name__ == "__main__":
    print(problem236A())