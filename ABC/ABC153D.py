def ABC153D() -> int:
    n = int(input())
    return (1 << n.bit_length()) - 1
  
print(ABC153D())