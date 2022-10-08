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


# declare variables
pm_number = 524287
pm_included = False
users = 1_000_000  # number of telephone users
friend_prop_limit = 0.99  # proportion of friends of friends of ... of PM
network = [-1]*users

caller, called = 0, 0  # initialize caller, called variables
unsuccessful_calls = 0

# loop through calls until proportion of friends of PM found
for call, i in enumerate(lagged_fib_gen(), start=1):
    if i == pm_number:  # if PM is called
        pm_included = True

    if call % 2 == 1:  # caller reached called
        if not caller == called:  # if not misdial
            graph_1, graph_2 = 0, 0
            s = 0
            
            # TODO disjoint-set data structure

            if pm_included:  # check if PM was already reached
                for graph in network:
                    if pm_number in graph:
                        friends = graph
                if len(friends) >= friend_prop_limit * users:
                    break
                
        else:  # misdial
            unsuccessful_calls += 1
        caller = i
    else:
        called = i
    
# print results
print(call // 2 - unsuccessful_calls)
