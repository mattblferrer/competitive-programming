#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> p(n + 1), pref(n + 2, n), suff(n + 2);
    for (ll i = 1; i <= n; i++) cin >> p[i];
    for (ll i = 1; i <= n; i++) {
        pref[i] = min(pref[i - 1], p[i]);
    }
    for (ll i = n; i >= 1; i--) {
        suff[i] = max(suff[i + 1], p[i]);
    }
    for (ll i = 1; i <= n; i++) {
        if (pref[i - 1] > suff[i]) { cout << "No\n"; return; }
    }

    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}