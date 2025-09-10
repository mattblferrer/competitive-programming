def ABC121A() -> int:
    H, W = map(int, input().split(" "))
    h, w = map(int, input().split(" "))

    return H * W - h * W - H * w + h * w

print(ABC121A())