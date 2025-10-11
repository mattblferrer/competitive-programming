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
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    ll ans = 0, lower = 0;
    for (const auto& pair: cnt) {
        ll num = pair.first, f = pair.second;
        ans += (f * (f - 1LL) * (f - 2LL) / 6LL) + (lower * f * (f - 1LL) / 2LL);
        lower += f;
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