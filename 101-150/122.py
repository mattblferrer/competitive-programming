# returns the multiplication chain with n multiplied by chain[index]
def mult_exp_chain(chain: list, index: int, limit: int) -> list[int]:
    new_chain = None
    new_exp = chain[-1] + index

    if new_exp <= limit:
        new_chain = chain.copy()
        new_chain.append(new_exp)

    return new_chain


# returns the array of chain multiplications below limit
def mult_chain(chains: list, limit: int) -> list:
    # initialize chain length array for checking 
    chain_length = [float('inf')] * (limit + 1)
    chain_length[1] = 1

    for index, n in enumerate(chains):  # index -> maximum exponent 
        if not n:   # check if n has chains
            continue 

        # generate new chains
        for chain in n:
            for i in chain:
                new_chain = mult_exp_chain(chain, i, limit)
                if not new_chain:  # if no new chain can be made
                    continue

                max_exp = new_chain[-1]  # maximum exponent reached by chain
                new_chain_length = len(new_chain)
                check_chain_length = chain_length[max_exp]
                
                # check if a chain does not exist or if chain is more efficient
                if not chains[max_exp] or new_chain_length < check_chain_length: 
                    chains[max_exp] = [new_chain]
                    chain_length[max_exp] = new_chain_length

                # if chain is just as efficient, add choice to list
                elif new_chain_length == check_chain_length:
                    chains[max_exp].append(new_chain)

        ways = len(n)  # how many minimum chains there are for n 
        print(index, ways, chain)  # track progress of function

    return chains  # return list of minimum chains for each k below limit
 

def main():
    # declare variables
    k = 200
    # list of minimum multiplication chains
    min_mults = [[] for _ in range(k + 1)]  

    # calculate all possible minimum chains of multiplications to get to n^k
    min_mults[1] = [[1]]  # n^1 (only one way)
    min_mults = mult_chain(min_mults, k)[1:]   # not counting 0

    # calculate sum of all m(k) below limit k
    min_mults = [chains[0] for chains in min_mults]
    mk = [len(chain) - 1 for chain in min_mults]

    # print result
    print(f"Sum of m(k): {sum(mk)}")


if __name__ == "__main__":
   main()
