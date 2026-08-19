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
    vector<ll> deg(n + 1);
    vector<vector<ll>> adj(n + 1);
    map<pll, ll> mp;
    for (ll i = 1; i <= n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        deg[u]++;
        deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
        mp[{u, v}] = i;
    }
    ll root = -1;
    for (ll i = 1; i <= n; i++) {
        if (deg[i] > 2) {
            cout << "-1\n";
            return;
        }
        if (deg[i] == 1) root = i;
    }

    vector<ll> seen(n + 1), ans(n + 1);
    queue<ll> q;
    seen[root] = true;
    q.push(root);
    ll parity = 0; // even
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        seen[u] = true;

        for (ll v : adj[u]) {
            if (seen[v]) continue;
            q.push(v);

            ans[mp[{min(u, v), max(u, v)}]] = 2 + parity;
            parity = 1 - parity;
        }
    }
    for (ll i = 1; i <= n - 1; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}