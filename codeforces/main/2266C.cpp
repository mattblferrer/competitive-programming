#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

bool is_sorted(string s) {
    for (ll i = 0; i < s.size() - 1; i++) {
        if ((s[i] == '1') && (s[i + 1] == '0')) return false;
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    if (is_sorted(s)) {
        cout << "0\n";
        return;
    }
    if (s[0] == '1') {
        ll ct0 = 0;
        for (ll i = 0; i < n; i++) {
            if (s[i] == '0') ct0++;
        }
        cout << ct0 << "\n";
        return;
    }

    s = ' ' + s;  // 1 index
    ll ans = INF;
    vector<ll> pref(n + 1);
    for (ll i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (s[i] == '1');
    }
    for (ll i = 0; i <= n; i++) {
        ll fi = pref[i];
        ll se = (n - i) - (pref[n] - pref[i]);
        ans = min(ans, fi + se);
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