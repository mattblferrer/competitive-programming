# returns the multiplication chain with n multiplied by chain[index]
def mult_exp_chain(chain: list, index: int, limit: int) -> list:
    new_chain = chain.copy()
    new_exp = chain[-1] + index

    if new_exp <= limit:
        new_chain.append(new_exp)

    return new_chain


# returns the array of chain multiplications with limit
def mult_chain(chains: list, limit: int) -> list:
    for index, n in enumerate(chains):  # index -> maximum exponent 
        if n:   # check if n has chains
            # generate new chains
            for chain in n:
                for i in chain:
                    new_chain = mult_exp_chain(chain, i, limit)
                    max_exp = new_chain[-1]  # maximum exponent reached by new chain
                    
                    # check if a chain does not exist
                    if not chains[max_exp]: 
                        chains[max_exp].append(new_chain)
                        
                    # if a chain exists, then...
                    else:
                        for check_chain in chains[max_exp]:
                            # check if chain generated is more efficient
                            if len(new_chain) < len(check_chain):
                                chains[max_exp] = [new_chain]

                            # if chain is just as efficient, add choice to list
                            if len(new_chain) == len(check_chain) and new_chain not in chains[max_exp]:
                                chains[max_exp].append(new_chain)
                                break

            ways = len(n)  # how many minimum chains there are for n 
            print(index, ways, n[0])  # track progress of function

    return chains  # return list of minimum chains for each k below limit
 

# declare variables
k = 200
minMults = [[] for _ in range(k+1)]  # list of minimum multiplication chains

# calculate all possible minimum chains of multiplications to get to n^k
minMults[1] = [[1]]  # n^1 (only one way)
minMults = mult_chain(minMults, k)[1:]   # not counting 0

# calculate sum of all m(k) below limit k
minMults = [chains[0] for chains in minMults]
mk = [len(chain) - 1 for chain in minMults]
sum_mk = sum(mk)

# print result
print(f"Sum of m(k): {sum_mk}")
