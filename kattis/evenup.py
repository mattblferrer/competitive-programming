_ = input()  # number of cards
cards = list(map(int, input().split(" ")))
stack = []

for c in cards:
    if not stack:
        stack.append(c)
        continue
    if (stack[-1] + c) % 2 == 0:
        stack.pop()
    else:
        stack.append(c)

print(len(stack))