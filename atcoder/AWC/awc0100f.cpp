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
    vector<ll> v(n + 1);
    for (ll i = 1; i <= n; i++) cin >> v[i];
    vector<ll> pref_v(n + 1);
    for (ll i = 1; i <= n; i++) pref_v[i] = pref_v[i - 1] + v[i];

    ll ans = 0;
    for (ll i = 0; i <= n; i++) {
        ll idx = distance(pref_v.begin() + 1, lower_bound(pref_v.begin(), pref_v.end(), pref_v[i] + k));
        ans += n - idx;
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