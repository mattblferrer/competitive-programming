words = input().split(" ")
for i in range(len(words) // 2, len(words)):
    print(f"{words[i]}", end=" ")
for i in range(len(words) // 2):
    print(f"{words[i]}", end=" ")
