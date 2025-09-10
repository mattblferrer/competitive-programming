def problem456B() -> int:
    n = int(input()[-2:]) % 4  # get remainder of n when divided by 4
    mod1 = [1, 1, 1, 1]  # last digit of 1^n
    mod2 = [6, 2, 4, 8]  # last digit of 2^n
    mod3 = [1, 3, 9, 7]  # last digit of 3^n
    mod4 = [6, 4, 6, 4]  # last digit of 4^n
    
    return (mod1[n] + mod2[n] + mod3[n] + mod4[n]) % 5

print(problem456B())