if __name__ == '__main__':
    s = input()
    print("True" if any(c.isalnum() for c in s) else "False")
    print("True" if any(c.isalpha() for c in s) else "False")
    print("True" if any(c.isdigit() for c in s) else "False")
    print("True" if any(c.islower() for c in s) else "False")
    print("True" if any(c.isupper() for c in s) else "False")
    