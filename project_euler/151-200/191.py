from functools import cache
        

@cache
def prize_string_nums(n: int, absent: int, late: int) -> int:
    """returns the number of prize strings that start with a given string 
    below a given length
    
    parameters:
    n: length of prize string
    absent: number of consecutive absent days at the end of the prize string 
    late: number of total late days in the string"""
    if n == 0:  # base case
        return 1

    string_num = prize_string_nums(n - 1, 0, late)  # O can be added
    if not late:  # L can be added
        string_num += prize_string_nums(n - 1, 0, 1)
    if absent < 2:  # A can be added
        string_num += prize_string_nums(n - 1, absent + 1, late)

    return string_num
        

def main():
    print(prize_string_nums(30, 0, 0))  # print result


if __name__ == "__main__":
    main()
