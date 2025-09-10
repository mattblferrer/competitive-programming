from collections import deque


# returns each term of a lagged fibonacci generator
def lagged_fib_gen() -> int:
    terms = deque([])
    i = 0  # starting num
    while True: 
        i += 1
        if i <= 55:  # terms 1 to 55
            term = (100003 - 200003*i + 300007*i*i*i) % users
        else:  # terms 56 to n
            term = (terms[31] + terms[0]) % users

        terms.append(term)
        yield term

        if len(terms) > 55:  # check if more than 55 terms in terms array
            terms.popleft()


# find in disjoint set data structure
def find_ds(node: int) -> int:
    if network[node] != node:  # check if root
        network[node] = find_ds(network[node])
        return network[node]
    return node


# union in disjoint set data structure
def union_ds(x: int, y: int) -> None:
    x, y = find_ds(x), find_ds(y)

    if x != y:  # two elements are not in the same tree
        network[y] = x
        network_size[x] += network_size[y]


# declare variables
pm_number = 524287
pm_included = False
users = 1_000_000  # number of telephone users
friend_prop_limit = 0.99  # proportion of friends of friends of ... of PM
caller, called = 0, 0  # initialize caller, called variables
unsuccessful_calls = 0

# create network
network = [i for i in range(users+1)]
network_size = [1]*(users+1)

# loop through calls until proportion of friends of PM found
for call, n in enumerate(lagged_fib_gen(), start=1):
    if n == pm_number:  # if PM is called
        pm_included = True

    if call % 2 == 0:  # caller reached called
        caller = n
        if not caller == called:  # if not misdial
            union_ds(caller, called)

            if call % 100_000 == 0:  # progress tracker
                print(f"call: {call // 2}, network size: {max(network_size)}")
            
            # check if PM was already reached
            if pm_included and (network_size[find_ds(pm_number)] 
                >= friend_prop_limit * users):  
                    break
                
        else:  # misdial
            unsuccessful_calls += 1
    else:
        called = n
    
# print results
print(f"Number of calls: {call // 2 - unsuccessful_calls}")
