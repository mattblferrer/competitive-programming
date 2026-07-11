#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

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
    vector<pll> h(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll hi;
        cin >> hi;
        h[i] = {hi, i};
    }

    vector<vector<ll>> adj_list(n + 1);
    for (ll i = 1; i <= m; i++) {
        ll a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    sort(h.begin() + 1, h.end());
    ll ans = INF;
    for (ll i = 1; i <= n; i++) {
        dsu d(n + 1);
        vector<bool> seen(n + 1);

        for (ll j = i; j <= n; j++) {
            ll v = h[j].second;
            seen[v] = true;
            for (ll u : adj_list[v]) {
                if (seen[u]) d.union_sets(u, v);
            }
            if (d.is_connected(1, 2)) {
                ans = min(ans, h[j].first - h[i].first);
                break;
            }
        }
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