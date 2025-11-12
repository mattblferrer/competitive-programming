def main():
    n = int(input())
    for _ in range(n):
        curr = []
        for _ in range(10):
            line = input()
            if line[0:2] == "@a":
                continue
            elif line == "}":
                continue
            if line[-1] != ',': 
                line += ','
            curr.append(line)
        curr.sort()

        authors = list(author.split(" ") for author in curr[0][8:-2].split(", "))
        journal = curr[1][9:-2]
        number = curr[2][8:-2]
        pages = curr[3][7:-2]
        publisher = curr[4][11:-2]
        title = curr[5][7:-2]
        volume = curr[6][8:-2]
        year = curr[7][6:-2]

        for author in authors[:-1]:
            print(author[0][0:2] + ". " + author[1][0], end=", ")
        print(authors[-1][0][0:2] + ". " + authors[-1][1][0], end=". ")
        print(f"{title}. {journal}. {year};{volume}({number}):{pages}.")

if __name__ == "__main__":  
    t = int(input())
    for _ in range(t): main()