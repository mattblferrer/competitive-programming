#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> x(n);
    for (ll i = 0; i < n; i++) cin >> x[i];

    ll ans = 0, pos = x[0];
    for (ll i = 1; i < n; i++) {
        ans += min((x[i] - x[i - 1]) * a, b);
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