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
    vector<vector<ll>> adj_list(n);
    vector<ll> deg(n);
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    ll start = 0, mid = 0, end = 0, x = 0, y = 0;
    for (ll i = 0; i < n; i++) {
        if (deg[i] == 1) {
            start = i;
            mid = adj_list[start][0];
            y = deg[mid] - 1;
            for (ll j = 0; j < deg[mid]; j++) {
                if (deg[adj_list[mid][j]] != 1) {
                    end = adj_list[mid][j];
                    x = deg[end];
                }
            }
            break;
        }
    }
    cout << x << " " << y << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}