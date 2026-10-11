#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> l(n + 1), r(n + 1);
    for (ll i = 2; i <= n; i++) cin >> l[i];
    for (ll i = 1; i <= n - 1; i++) cin >> r[i];

    vector<ll> pref_min(n + 2, INF), suff_min(n + 2, INF);
    for (ll i = 1; i <= n - 1; i++) {
        pref_min[i] = min(pref_min[i - 1], r[i]);
    }
    for (ll i = n; i >= 2; i--) {
        suff_min[i] = min(suff_min[i + 1], l[i]);
    }
    for (ll qi = 1; qi <= q; qi++) {
        ll s, t;
        cin >> s >> t;
        ll ans;
        if (s < t) {
            ans = min(r[s], pref_min[s] + l[s]);
        }
        else {
            ans = min(l[s], suff_min[s] + r[s]);
        }
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}