#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct dsu {
    vector<int> parent, sz;

    dsu(int a) {
        parent.resize(a);
        sz.resize(a, 1);
        for (int i = 0; i < a; i++) parent[i] = i;
    }

    int find_set(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find_set(parent[a]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool is_connected(int a, int b) { return find_set(a) == find_set(b); }
};

bool cycle_dfs(int u, int parent, vector<vector<ll>> &adj, vector<bool> &seen) {
    seen[u] = true;
    for (ll v : adj[u]) {
        if (!seen[v]) {
            if (cycle_dfs(v, u, adj, seen)) return true;
        }
        else if (v != parent) return true;
    }
    return false;
}

void bfs(ll start, vector<vector<ll>> &adj, vector<ll> &dist) {
    queue<ll> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v : adj[u]) {
            if (dist[v] != INF) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    dsu ds(n);
    for (ll i = 0; i < m; i++) {
        ll ui, vi;
        cin >> ui >> vi;
        ui--; vi--;
        adj[ui].push_back(vi);
        adj[vi].push_back(ui);
        ds.union_sets(ui, vi);
    }
    for (ll i = 0; i < n; i++) {
        if (adj[i].size() == 0) {
            cout << "Brain Melt\n";
            return;
        }
    }

    set<ll> parents;
    for (ll i = 0; i < n; i++) {
        parents.insert(ds.find_set(i));
    }
    if (parents.size() > 1) {
        cout << "Many\n";
        return;
    }
    vector<bool> seen(n);
    if (cycle_dfs(0, -1, adj, seen)) {
        cout << "Many\n";
        return;
    }

    vector<ll> dist(n, INF);
    bfs(0, adj, dist);
    ll max_dist = 0, max_i = 0;
    for (ll i = 0; i < n; i++) {
        if (max_dist < dist[i]) {
            max_dist = dist[i];
            max_i = i;
        }
    }
    dist.assign(n, INF);
    bfs(max_i, adj, dist);
    ll diameter = 0;
    for (ll i = 0; i < n; i++) {
        diameter = max(diameter, dist[i]);
    }
    if (diameter >= 3) cout << "Many\n";
    else cout << "2\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}