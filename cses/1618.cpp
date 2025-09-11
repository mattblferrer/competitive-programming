#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

ll CSES1618() {
    ll n;
    std::cin >> n;
    ll ans = 0;
    for (int i = 5; i <= n; i *= 5) {
        ans += n / i;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1618();
    return 0;
}