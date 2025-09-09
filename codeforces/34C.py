def problem34C() -> str:
    pages = sorted(map(int, input().split(",")))

    # get page intervals
    intervals = []
    low, high = pages[0], pages[0]

    for i in range(1, len(pages)):  
        if pages[i] - pages[i - 1] > 1:  # new interval
            intervals.append((low, high))
            low = pages[i]
            high = pages[i]
        else:  # continue interval
            high = pages[i]
    intervals.append((low, high))
    
    # format intervals to page number format 
    output = ""  
    for i, (low, high) in enumerate(intervals):  
        if low == high:  # one page
            output += f"{low}"
        else:  # multiple pages
            output += f"{low}-{high}"
        if i < len(intervals) - 1:  # comma separator
            output += ","

    return output

print(problem34C())