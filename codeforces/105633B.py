def bin_to_int(s):
    ans = 0
    c = 1
    for i in range(1, len(s) + 1):
        if s[-i] == "1":
            ans += c
        c *= 2
    return ans

def solve_fast(a, b):
    bin_a = str(bin(a))[2:]
    bin_b = str(bin(b))[2:]
    bin_a = bin_a.zfill(len(bin_b))

    ans = bin_a
    flag = False
    for i in range(len(bin_a)):
        if bin_a[i] == "0" and bin_b[i] == "1":
            for j in range(i, len(bin_a) - 1):
                if bin_a[j + 1] == "1":
                    ans = bin_a[:j] + "1" + "0" * (len(bin_a) - j - 1)
                    flag = True
                    break
            else:
                return a
            if flag: break
    else:
        return a
    
    if ans.count("1") == bin_a.count("1"):
        return a
    return bin_to_int(ans)

a, b = map(int, input().split())
print(solve_fast(a, b))
