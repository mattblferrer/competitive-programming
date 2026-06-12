#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<bool> taken(m + 1);
    for (ll i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        for (ll j = l; j <= r; j++) taken[j] = true;
    }
    vector<ll> ans;
    for (ll i = 1; i <= m; i++) {
        if (!taken[i]) ans.push_back(i);
    }
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}