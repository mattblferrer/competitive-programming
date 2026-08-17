#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < m; i++) cin >> b[i];

    ll as = a.back(), bs = b.back();
    for (ll i = 0; i < n - 1; i++) as += a[i] - a[i + 1] + 1;
    for (ll i = 0; i < m - 1; i++) bs += b[i] - b[i + 1] + 1;
    if (as >= bs) cout << "1\n";
    else cout << "2\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}