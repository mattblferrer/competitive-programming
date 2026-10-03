#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 998244353;

long long power(long long base, long long exp, long long mod) {
    base %= mod;
    if (base < 0) base += mod;
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;
    for (ll i = 0; i < q; i++) {
        ll xi, yi;
        cin >> xi >> yi;
    }
    ll ans = power(m, n - q, MOD);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}