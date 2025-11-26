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
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        cnt[ai]++;
    }
    ll ans = 0, ext = 0;
    for (const auto& [k, c]: cnt) {
        ans += c*(c - 1)/2;
        if (k == 1) ext += c*cnt[2];
        else if (k == 2) ext += c*cnt[1];
    }
    ans += ext / 2;
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}