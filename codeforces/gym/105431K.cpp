#include <iostream>
using ll = long long;

int main() {
    ll n, p; std::cin >> n >> p;

    ll div = n / p;
    if ((n % p != 0) && ((div & 1) == 0)) div--;
    std::cout << n - (p * div);
}