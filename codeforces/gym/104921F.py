def problem1883A() -> int:
    pin = input()
    seconds = 0
    position = {1: 0, 2: 1, 3: 2, 4: 3, 5: 4, 6: 5, 7: 6, 8: 7, 9: 8, 0: 9}
    prev = "1"  # starting position of cursor
 
    for curr in pin:
        seconds += 1 + abs(position[int(curr)] - position[int(prev)])
        prev = curr
 
    return seconds
 
test_cases = int(input())
for _ in range(test_cases):
    print(problem1883A())