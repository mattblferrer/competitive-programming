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
    ll n, m;
    cin >> n >> m;
    dsu d(n + 1);
    for (ll i = 0; i < m; i++) {
        ll ui, vi;
        cin >> ui >> vi;
        d.union_sets(ui, vi);
    }
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll si;
        cin >> si;
        cout << d.sz[d.find_set(si)] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}