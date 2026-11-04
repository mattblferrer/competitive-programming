// github.com/mattblferrer/competitive-programming

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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (n % 2 == 0) {
        cout << n + 1 << "\n";
        return;
    }
    vector<dsu> d(3, dsu(n + 1));
    vector<pll> p = {{1, n + 2},{(n + 1) / 2, n + 1},{n, n}};
    for (int dc = 0; dc < 3; dc++) {
        auto [k, ans] = p[dc];
        d[dc] = dsu(n + 1);
        for (int i = 1; i <= n; i++) {
            if (i == k) continue;
            for (int j : adj[i]) {
                if (j == k) continue;
                d[dc].union_sets(i, j);
            }
        }
        for (int i = 1; i <= n; i++) {
            int j = ans - i;
            if (j > n) continue;
            if (!d[dc].is_connected(i, j)) {
                cout << ans << "\n";
                return;
            }
        }
    }

    cout << n + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}