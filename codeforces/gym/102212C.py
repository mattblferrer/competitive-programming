def main():
    words = input().split(" ")
    new_words = []
    for word in words:
        new_words.append(word[1:] + word[0].lower() + "ay")
    new_words[0] = new_words[0].capitalize()
    for word in new_words:
        print(word, end=" ")
    print()

if __name__ == "__main__":  
    t = int(input())
    for _ in range(t): main()