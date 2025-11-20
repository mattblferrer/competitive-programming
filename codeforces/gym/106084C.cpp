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
    vector<vector<ll>> conn(m);
    vector<ll> t(n);
    for (ll i = 0; i < m; i++) {
        ll x, y, v;
        cin >> x >> y >> v;
        x--; y--;
        conn[i] = {x, y, v};
    }
    for (ll i = 0; i < m; i++) {
        ll x = conn[i][0], y = conn[i][1], v = conn[i][2];
        ll tx_old = t[x], ty_old = t[y];
        t[x] = ty_old + v, t[y] = tx_old + v;
    }
    cout << *max_element(t.begin(), t.end()) << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}