# function to check if a year is a leap year
def leap_year(n: int) -> bool:  
    if n % 400 == 0:
        return True
    elif n % 100 == 0:
        return False
    elif n % 4 == 0:
        return True
    return False


def main():
    # declare variables
    days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    days_in_month_ly = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    start_year = 1901
    end_year = 2000
    current_day = 2  # 0 = Sunday, 1 = Monday, ...
    first_sundays = 0  # final output

    # calculate number of Sundays
    for year in range(start_year, end_year+1):  # iterate through every year
        for month in range(12):  # iterate through months
            if current_day % 7 == 0:  # check if current day is a Sunday
                first_sundays += 1
            if leap_year(year):
                current_day += days_in_month_ly[month]
            else:
                current_day += days_in_month[month]

    # print result
    print(f"Number of Sundays on the first of the month: {first_sundays}")


if __name__ == "__main__":
    main()
