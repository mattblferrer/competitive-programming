# returns the value of the generating function evaluated at n
def generating_function(n: int) -> int:
    return 1 - n + n*n - n**3 + n**4 - n**5 + n**6 - n**7 + n**8 - n**9 + n**10


# returns the FIT for the BOP of degree k given the past terms
def fit(k: int, terms: list[int]) -> int:
    if k == 1:  # assume constancy
        return generating_function(1)

    # get differences of adjacent terms
    diff_arr = terms
    last_term_arr = [terms[-1]]  # array of last terms in each difference array

    while len(diff_arr) > 1:
        new_arr = []

        for j, element in enumerate(diff_arr[:-1]):
            new_arr.append(diff_arr[j+1] - element)
        
        last_term_arr.append(new_arr[-1])
        diff_arr = new_arr
        
    return sum(last_term_arr)


def main():
    # declare variables
    degree = 10  # degree of the generating function
    sumFIT = 0  # sum of FITs for the BOPs
    terms = [1]  # confirmed terms

    # main loop through all BOPs
    for i in range(2, degree + 2):
        term = generating_function(i)
        sumFIT += fit(i, terms)
        terms.append(term)

    # print result
    print(sumFIT)


if __name__ == "__main__":
    main()
