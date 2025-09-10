import sys

def main():
    n, k = map(int, input().split())
    count = 0
    lines = 0

    for line in sys.stdin:
        lines += 1
        t_i = int(line)
        if t_i % k == 0:
            count += 1
        if lines == n:
            break
        
    print(count)

main()