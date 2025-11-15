def main():
    MOD = 104206969
    a, b = map(int, input().split(" "))
    year = 0
    months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    for m in range(1, 13):
        for d in range(1, months[m - 1] + 1):
            year += int(str(m) + str(d))

    ans = year * (b - a + 1)
    ly = ((b - b % 4) - (a - a % 4)) // 4 + (a % 4 == 0)
    ly -= ((b - b % 100) - (a - a % 100)) // 100 + (a % 100 == 0)
    ly += ((b - b % 400) - (a - a % 400)) // 400 + (a % 400 == 0)
    ans += ly * 229
    print(ans % MOD)

if __name__ == "__main__":  
    main()