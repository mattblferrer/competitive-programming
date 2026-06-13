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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) cnt[a[i]]++;

    ll max_pair = 0;
    ll ans;
    for (auto pair : cnt) {
        max_pair = max(max_pair, pair.second);
    }
    if (max_pair > cnt.size()) ans = min(max_pair, (ll)cnt.size());
    else ans = min(max_pair, (ll)cnt.size() - 1);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}