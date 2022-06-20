def leap_year(n):  # function to check if a year is a leap year
    if n % 400 == 0:
        return True
    elif n % 100 == 0:
        return False
    elif n % 4 == 0:
        return True
    else:
        return False


daysInMonths = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # non leap year
daysInMonthsLY = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # leap year
startYear = 1901
endYear = 2000
currentDay = 2  # 0 = Sunday, 1 = Monday, ...
firstSundays = 0  # final output

for year in range(startYear, endYear+1):  # iterate through every year
    for month in range(12):  # iterate through months
        if currentDay == 0:  # check if current day is a Sunday
            firstSundays += 1
        if leap_year(year):
            currentDay += daysInMonthsLY[month]
        else:
            currentDay += daysInMonths[month]
        currentDay = currentDay % 7  # for 7 days of the week

print("Number of Sundays on the first of the month: " + str(firstSundays))
