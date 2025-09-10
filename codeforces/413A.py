def problem413A() -> str:
    n, m, mi, ma = map(int, input().split(' '))
    m_list = list(map(int, input().split(' ')))

    if n == m:  # both (min, max) has to be correct
        if min(m_list) == mi and max(m_list) == ma:
            return "Correct"
        else:
            return "Incorrect"
    elif n - 1 == m:  # only one (min, max) has to be correct
        if min(m_list) == mi and max(m_list) <= ma:
            return "Correct"
        elif min(m_list) >= mi and max(m_list) == ma:
            return "Correct"
        else:
            return "Incorrect"
    else: 
        if min(m_list) < mi:  # lower minimum in assistant's list
            return "Incorrect"
        if max(m_list) > ma:  # higher maximum in assistant's list
            return "Incorrect"
        return "Correct"

print(problem413A())