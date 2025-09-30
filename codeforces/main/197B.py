from math import gcd

def problem197B() -> str:
    n, m = map(int, input().split(' '))
    p = list(map(int, input().split(' ')))
    q = list(map(int, input().split(' ')))

    if n > m:  # P(x) has higher degree than Q(x)
        if (p[0] > 0) == (q[0] > 0):
            return "Infinity"
        else:
            return "-Infinity"
        
    if n < m:  # Q(x) has higher degree than P(x)
        return "0/1"
    
    # P(x) has the same degree as Q(x)
    gcd_pq = gcd(p[0], q[0])
    if (p[0] > 0) == (q[0] > 0):  # positive limit
        return f"{abs(p[0] // gcd_pq)}/{abs(q[0] // gcd_pq)}"
    else:  # negative limit
        return f"-{abs(p[0] // gcd_pq)}/{abs(q[0] // gcd_pq)}"

print(problem197B())