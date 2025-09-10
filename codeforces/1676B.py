def problem1676B() -> int:
    _ = input()  # number of boxes
    boxes = list(map(int, input().split(" ")))
    min_candies = min(boxes)
    candies_needed = 0
    
    for b in boxes:
        candies_needed += b - min_candies

    return candies_needed

test_cases = int(input())
for _ in range(test_cases):
    print(problem1676B())