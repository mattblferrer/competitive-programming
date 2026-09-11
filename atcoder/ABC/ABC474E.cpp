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
    vector<pll> p(n);
    ll min_ai = INF;
    for (ll i = 0; i < n; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        p[i] = {ai, bi};
        min_ai = min(min_ai, ai);
    }

    sort(p.begin(), p.end(), [](pll a, pll b) {
        return a.second - a.first < b.second - b.first;
        });
    ll ans = 0, curr = 0;
    for (ll i = 0; i < n; i++) {
        auto &[ai, bi] = p[i];
        ans += ai;
        curr += ai;
    }

    for (ll i = 0; i < n; i++) {
        auto &[ai, bi] = p[i];
        curr -= (ai - bi);
        ans = min(ans, curr + max(0LL, -(n - 2 * (i + 1))) * min_ai);
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