#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
ll MOD = pow(10, 9) + 7;

long long binexp(long long a, long long b, long long mod) {
    long long ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

ll CSES1712() {
    ll a, b, c;
    std::cin >> a >> b >> c;
    return binexp(a, binexp(b, c, MOD - 1), MOD);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll n;
    std::cin >> n;
    for (ll i = 0; i < n; i++) {
        std::cout << CSES1712() << "\n";
    }
    return 0;
}