#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    __int128_t sum = (__int128_t)(k) * ((__int128_t)(k)+1) / 2;
    if (sum > n) { cout << "-1\n"; return; }

    vector<ll> a(k + 1);
    for (ll i = 1; i <= k; i++) a[i] = i;

    vector<ll> factors;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (i * i != n) factors.push_back(n / i);
        }
    }

    ll scale = n / sum, max_gcd = 0;
    for (ll f : factors) {
        if (f <= scale) max_gcd = max(max_gcd, f);
    }
    for (ll i = 1; i <= k; i++) a[i] *= max_gcd;
    sum *= max_gcd;
    a[k] += n - sum;
    for (ll i = 1; i <= k; i++) cout << a[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}