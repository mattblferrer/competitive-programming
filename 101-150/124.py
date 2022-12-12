from collections import defaultdict


# iterates through dict and finds nth element
def find_element_124(d: dict[int], n: int) -> int:
    index = 0

    for value_list in d.values():
        for value in value_list:
            if index == n:
                return value           
            index += 1


def main():
    # returns the radical of num + whether it is prime
    def radical_pr(num: int) -> tuple:
        if num in (0, 1):
            return num, False
        
        radical = 1
        original_num = num  # for prime check

        # calculate the radical
        for prime in prime_list:
            if prime * prime > num:  # we don't have to check these numbers
                break

            if num % prime == 0:
                radical *= prime

                while num % prime == 0:
                    num //= prime

        # check if prime
        if num != 1 and num != original_num:
            radical *= num
            return radical, False

        return radical, True


    # declare variables
    prime_list = [2]
    rad_dict = defaultdict(list)  # keys are rad(n), values are n
    limit = 100_000

    # fill in dict with radical values
    for i in range(limit + 1):
        rad, _ = radical_pr(i)

        if i != 1 and rad == 1:  # prime number check
            rad_dict[i].append(i)
            prime_list.append(i)
        else:
            rad_dict[rad].append(i)

    answer = find_element_124(rad_dict, 10000)

    # print result
    print(f"E(10000) = {answer}")


if __name__ == "__main__":
    main()
