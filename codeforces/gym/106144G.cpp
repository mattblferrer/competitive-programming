#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string s;
    cin >> s;
    s += '0';  // sentinel
    ll n = s.size();

    map<ll, vector<ll>> runs;
    map<ll, ll> cnt;
    ll curr = 0;
    char last = s[0];
    for (ll i = 0; i < n; i++) cnt[s[i]]++;
    for (ll i = 0; i < n; i++) {
        if (last == s[i]) curr++;
        else {
            runs[last].push_back(curr);
            curr = 1;
        }
        last = s[i];
    }

    ll ans = 1;
    for (auto &[c, v] : cnt) {
        if (c == '0') continue;
        ans += (v * (v + 1)) / 2;
        for (ll k : runs[c]) {
            ans -= ((k - 1) * k) / 2;
        }
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