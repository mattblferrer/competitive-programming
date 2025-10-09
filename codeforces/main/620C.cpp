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
    vector<pll> ans;

    set<ll> seen;
    ll l = 0;
    for (ll r = 0; r < n; r++) {
        if (seen.count(a[r])) {
            seen.clear();
            ans.push_back({l + 1, r + 1});
            l = r + 1;
        }
        else seen.insert(a[r]);
    }
    if (ans.size()) ans.back() = {ans.back().first, n};
    if (ans.size() == 0) {
        cout << -1;
        return;
    }
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}