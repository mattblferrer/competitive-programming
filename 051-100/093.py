from itertools import permutations, combinations_with_replacement


# returns the result from an expression in Reverse Polish Notation
def rpn_evaluate(exp):
    stack = []

    try:
        for char in exp:  # read expression from left to right
            if str(char).isdigit():  # if number
                stack.append(int(char))
            else:  # if operator, pop two from stack
                a, b = stack.pop(), stack.pop()

                # evaluate and push back to stack
                if char == "+":
                    stack.append(float(a+b))
                elif char == "-":
                    stack.append(float(a-b))
                elif char == "*":
                    stack.append(float(a*b))
                elif char == "/":
                    stack.append(float(a/b))

    except:  # invalid RPN notation (stack too short)
        return "Invalid"
    return stack[0]
        

# evaluates all possible combinations of operations for a given set of digits
def rpn_combination(digit_set):
    all_operations = ["+", "-", "*", "/"]
    answer_set = set()

    # last character in valid RPN is always an operator
    for opr in all_operations:
        # generate all possible combinations of operations
        for opr_set in combinations_with_replacement(all_operations, 2): 

            # first two characters in valid RPN are always numbers
            for digit_comb in permutations(digit_set):
                total_set = digit_comb[2:] + opr_set

                # evaluate RPN
                for perm in permutations(total_set):
                    # construct RPN expression
                    answer = rpn_evaluate(list(digit_comb[:2] + perm + tuple(opr)))

                    if answer != "Invalid" and answer > 0:
                        if float(answer).is_integer():
                            answer_set.add(answer)

    # return n from longest set of consecutive 1 to n evaluated
    answer_set = list(answer_set)

    for i in range(len(answer_set) - 1):
        if answer_set[i+1] != answer_set[i] + 1:
            return i+1


# generates increasing combinations of digits
def digit_generator() -> list[int]:
    for a in range(1, 7):
        for b in range(a+1, 8):
            for c in range(b+1, 9):
                for d in range(c+1, 10):
                    yield([a, b, c, d])


# generate strictly increasing 4-set of numbers of 1 through 9
digitGenerator = digit_generator()

# main loop
maximumN = 0

for combination in digitGenerator:
    n = rpn_combination(combination)
    print(n, combination)
    
    if maximumN < n:
        maximumN = n
        maximumABCD = combination
    
# print result
print("The longest set of positive integers 1 to n can be obtained with",
    "digit set", maximumABCD)
