#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> a;
vector<set<ll>> adj;
vector<pll> edges;
vector<bool> seen;
set<ll> leaves;

void solve()
{
    ll n;
    cin >> n;
    a.assign(n + 1, 0);
    adj.assign(n + 1, set<ll>());
    edges.clear();
    seen.assign(n + 1, false);
    leaves.clear();

    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i <= n - 1; i++) {
        ll ui, vi;
        cin >> ui >> vi;
        adj[ui].insert(vi);
        adj[vi].insert(ui);
    }
    for (ll i = 1; i <= n; i++) {
        if (adj[i].size() == 1) leaves.insert(i);
    }

    bool moved = true;
    while (moved) {
        moved = false;
        set<ll> new_leaves;
        for (ll v : leaves) {
            ll u = *(adj[v].begin());

            if (a[u] > a[v]) {
                a[u] += a[v];
                edges.push_back({u, v});

                moved = true;
                adj[u].erase(v);
                adj[v].erase(u);
                if (adj[u].size() == 1) new_leaves.insert(u);
                if (adj[v].size() == 1) new_leaves.insert(v);
            }
            else new_leaves.insert(v);
        }
        leaves = new_leaves;
    }

    if (edges.size() < n - 1) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for (ll i = 0; i < n - 1; i++) {
        cout << edges[i].first << " " << edges[i].second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}