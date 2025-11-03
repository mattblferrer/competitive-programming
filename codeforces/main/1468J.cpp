#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> parent;
vector<ll> sz;

void make_set(ll a) {
    parent[a] = a;
    sz[a] = 1;
}

ll find_set(ll a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

bool is_connected(ll a, ll b) {
    return find_set(a) == find_set(b);
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    parent.resize(n + 1);
    sz.resize(n + 1);
    for (ll i = 0; i <= n; i++) make_set(i);  // init dsu

    // find edge with min abs difference from k
    vector<vector<ll>> edges(m);
    vector<ll> min_edge(3);
    ll min_diff = INF;
    for (ll i = 0; i < m; i++) {
        ll x, y, s;
        cin >> x >> y >> s;
        edges[i] = {x, y, s};
        if (abs(s - k) < min_diff) {
            min_diff = abs(s - k);
            min_edge = {x, y, s};
        }
    }

    // kruskal's algorithm
    vector<vector<ll>> mst;
    sort(edges.begin(), edges.end(), [](vector<ll> a, vector<ll> b){
        return a[2] < b[2];
    });
    for (auto edge: edges) {
        ll x = edge[0], y = edge[1], s = edge[2];
        if (!union_sets(x, y)) continue;
        mst.push_back({x, y, s});
    }

    // redo kruskal's algorithm if max speed limit less than k
    if (mst.back()[2] < k) {
        mst.clear();
        for (ll i = 0; i <= n; i++) make_set(i);  // init dsu
        mst.push_back(min_edge);
        union_sets(min_edge[0], min_edge[1]);
        for (auto edge: edges) {
            ll x = edge[0], y = edge[1], s = edge[2];
            if (!union_sets(x, y)) continue;
            mst.push_back({x, y, s});
        }
    }
    sort(mst.begin(), mst.end(), [](vector<ll> a, vector<ll> b){
        return a[2] < b[2];
    });

    // output speed limit change
    ll ans = 0;
    for (auto edge: mst) {
        ll x = edge[0], y = edge[1], s = edge[2];
        ans += max(0LL, s - k);
    }
    ans += max(0LL, k - mst.back()[2]);
    cout << ans << '\n';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}