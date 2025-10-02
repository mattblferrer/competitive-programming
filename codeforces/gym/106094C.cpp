#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

map<ll, ll> factorize(ll n) {
    map<ll, ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n != 1) factors[n]++;
    return factors;
}

void solve() {
    ll x, k;
    cin >> x >> k;
    map<ll, ll> factors = factorize(x);
    for (ll lotus = 0; lotus <= 64; lotus++) {
        ll curr = 1LL << lotus;
        for (const auto& pair: factors) {
            if (pair.second % curr == 0) continue; 
            ll diff = curr - (pair.second % curr);
            factors[pair.first] += diff;
            k -= diff;
        }
        if (k < 0) {
            cout << lotus - 1 << '\n';
            return;
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}