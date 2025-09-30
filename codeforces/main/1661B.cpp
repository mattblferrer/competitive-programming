#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

ll solve_one(ll n) {
    ll ans = INF;
    for (ll j = 0; j < 16; j++) {
        ll x = (n + j) % 32768;
        for (ll k = 0; k < 16; k++) {
            if (x == 0) ans = min(ans, j + k);
            x = (x * 2) % 32768;
        }
    }
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cout << solve_one(a[i]) << " ";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}