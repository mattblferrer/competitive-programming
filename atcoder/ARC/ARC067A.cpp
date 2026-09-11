#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> factors(1000);
    for (ll i = 2; i <= n; i++) {
        ll curr = i;
        for (ll j = 2; j*j <= i; j++) {
            while (curr % j == 0) {
                factors[j]++;
                curr /= j;
            }
        }
        if (curr > 1) factors[curr]++;
    }
    ll ans = 1;
    for (ll i = 0; i < 1000; i++) {
        if (factors[i] == 0) continue;
        ans = (ans * (factors[i] + 1)) % MOD;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}