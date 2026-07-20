#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, s;
    cin >> n >> m >> s;
    vector<ll> a(n), b(m);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < m; i++) cin >> b[i];

    ll daily = 0, sum_a = 0, sum_b = 0;
    for (ll i = 0; i < n; i++) sum_a += a[i];
    for (ll i = 0; i < m; i++) sum_b += b[i];
    daily = sum_a - sum_b;
    if (daily >= 0) {
        cout << "-1\n";
        return;
    }
    cout << -s / daily;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}