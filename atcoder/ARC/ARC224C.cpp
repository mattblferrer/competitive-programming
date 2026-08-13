#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<vector<ll>> adj;
vector<ll> a;

void dfs(ll u) {
    for (ll v: adj[u]) {
        if (a[v] != -1) continue;
        a[v] = a[u] + 1;
        dfs(v);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    adj.assign(n + 1, vector<ll>());
    a.assign(n + 1, -1);
    a[1] = 0;

    for (ll i = 1; i <= m; i++) {
        ll ui, vi;
        cin >> ui >> vi;
        adj[ui].push_back(vi);
        adj[vi].push_back(ui);
    }

    dfs(1);
    for (ll i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}