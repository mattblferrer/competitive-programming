#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

void problem2117B() {
    ll n;
    std::cin >> n;
    for (ll i = 1; i <= n; i += 2) std::cout << i << " ";
    for (ll i = n - n % 2; i > 0; i -= 2) std::cout << i << " ";
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2117B();
    }
    return 0;
}