#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 998244353;

void solve() {
    ll n;
    cin >> n;
    vector<ll> p(n + 1);
    for (ll i = 1; i <= n; i++) cin >> p[i];

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (p[i] != i) break;
        ans = (ans + max(1LL, n - i)) % MOD;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}