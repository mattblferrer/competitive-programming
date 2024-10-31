def ABC190D() -> int:
    n = int(input())
    odd_factors = 1  # including 1
    if n != 1 and n % 2 == 1:  # including itself if odd
        odd_factors += 1

    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            if i % 2 == 1:
                odd_factors += 1
            if i != (n // i) and (n // i) % 2 == 1:
                odd_factors += 1
    
    return odd_factors * 2

print(ABC190D())