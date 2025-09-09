#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

std::string problem2117D() {
    ll n;
    std::cin >> n;
    std::vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    ll sum = 0, tri = n * (n + 1) / 2, diff = a[2] - a[1];
    for (ll i = 1; i <= n; i++) sum += a[i];
    if (sum % tri != 0) return "NO";
    if ((sum / tri) % 2 != abs(diff) % 2) return "NO";
    if (abs(diff) > sum / tri) return "NO";
    for (ll i = 1; i < n; i++) {
        if ((a[i + 1] - a[i]) != diff) return "NO";
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2117D() << "\n";
    }
    return 0;
}