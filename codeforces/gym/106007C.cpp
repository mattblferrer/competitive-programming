#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

bool is_valid(vector<ll> &pref, ll n, ll m, ll d) {
    for (ll i = 1; i <= n; i++) {
        ll new_i = distance(pref.begin(), upper_bound(pref.begin(), pref.end(), pref[i - 1] + m - d));
        if (new_i == n + 1) return true;

        ll jump = pref[new_i] - pref[i - 1];
        if (jump > m) return false;
        i = new_i;
    }
    return true;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];
    vector<ll> pref(n + 1);
    for (ll i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];

    for (ll d = 1; d <= m; d++) {
        if (is_valid(pref, n, m, d)) {
            cout << d << "\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}