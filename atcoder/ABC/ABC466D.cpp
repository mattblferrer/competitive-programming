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
    vector<vector<ll>> rows(n + 1), cols(n + 1);
    for (ll i = 0; i < m; i++) {
        ll ri, ci;
        cin >> ri >> ci;
        for (ll j = 0; j < rows[ri].size(); j++) {
            cols[rows[ri][j]].clear();
        }
        for (ll j = 0; j < cols[ci].size(); j++) {
            rows[cols[ci][j]].clear();
        }
        rows[ri] = {ci};
        cols[ci] = {ri};
    }
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans += rows[i].size();
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}