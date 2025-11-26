def main():
    k = int(input())
    for i in range(1, k):
        for j in range(1, k):
            curr = i*j
            cell = ""
            while curr > 0:
                cell += str(curr % k)
                curr //= k
            print(cell[::-1], end=" ")
        print()

if __name__ == "__main__":  
    main()