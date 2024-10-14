def ABC121C() -> int:
    n, m = map(int, input().split(" "))
    drink_costs = []
    money = 0

    for _ in range(n):  # get sorted list of costs, cheapest to most expensive
        A_i, B_i = map(int, input().split(" "))
        drink_costs.append((A_i, B_i))
    drink_costs.sort()

    for A_i, B_i in drink_costs:
        drinks_bought = min(m, B_i)
        money += A_i * drinks_bought
        m -= drinks_bought
        if m == 0:
            return money

print(ABC121C())