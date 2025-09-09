#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

std::string problem2117A() {
    ll n, x;
    std::cin >> n >> x;
    std::vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    bool used = false;
    for (int i = 0; i < n; i++) {
        if (x <= 0 && a[i] == 1) return "NO";
        if (a[i] == 1) used = true;
        if (used) x--;
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2117A() << "\n";
    }
    return 0;
}