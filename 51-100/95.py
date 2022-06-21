# returns the sum of the factors of num
def factors(num):
    factor_sum = 1  # all numbers have a factor of 1

    for i in range(2, int(num ** 0.5) + 1):  # only have to check for factors up to sqrt(n)
        if num % i == 0:
            factor_sum += i
            factor_sum += (num//i)

    return factor_sum


# declare variables
n = 15472  # given
limit = 1000000
max_chain_length = 5  # given

# main loop
# TODO

