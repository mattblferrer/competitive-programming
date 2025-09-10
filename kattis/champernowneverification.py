n = int(input())
if n in [1, 12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789]:
    print(len(str(n)))
else:
    print(-1)