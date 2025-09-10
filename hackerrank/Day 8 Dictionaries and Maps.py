# Enter your code here. Read input from STDIN. Print output to STDOUT
n = int(input())
phone_dict = {}

for _ in range(n):
    name, phoneNumber = input().split(" ")
    phone_dict[name] = int(phoneNumber)
    
while True:
    try:
        name = input()
        phoneNumber = phone_dict.get(name, 0)
        if phoneNumber:
            print(f"{name}={phoneNumber}")
        else:
            print("Not found")
    except:
        break
