#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

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
    int n, q, t, u, v;
    cin >> n >> q;
    dsu d(n + 1);
    for (int i = 0; i < q; i++) {
        cin >> t >> u >> v;
        if (t == 0) d.union_sets(u, v);
        if (t == 1) cout << d.is_connected(u, v) << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}