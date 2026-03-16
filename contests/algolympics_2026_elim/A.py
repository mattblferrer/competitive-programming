for _ in range(int(input())):
    x, y = map(int, input().split())
    n = int(input())
    m = input()
 
    k = (x + y + pow(130, x + y, 26)) % 26
 
    ans = []
    for char in m:
        ans.append(chr((ord(char) - 97 + k) % 26 + 97))
    print(''.join(ans))