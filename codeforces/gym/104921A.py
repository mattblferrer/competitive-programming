def problem1907A() -> None:
    square = input()
    column, row = square[0], square[1]
    cols = 'abcdefgh'
    for i in range(1, 9):  # print all moves in same column
        if str(i) != row:
            print(column + str(i))
 
    for i in range(8):  # print all moves in same row
        if cols[i] != column:
            print(cols[i] + row) 
 
test_cases = int(input())
for _ in range(test_cases):
    problem1907A()