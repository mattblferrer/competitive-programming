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
    ll n, m;
    cin >> n >> m;
    parent.resize(n + 1);
    sz.resize(n + 1);
    for (ll i = 1; i <= n; i++) make_set(i);

    // dsu data struct
    vector<ll> deg(n + 1);
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        union_sets(u, v);
    }

    // vertices of each connected component
    vector<vector<ll>> vert(n + 1);
    for (ll i = 1; i <= n; i++) vert[find_set(i)].push_back(i);
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (vert[i].size() == 0) continue;
        bool valid = true;
        for (ll u: vert[i]) {
            if (deg[u] != 2) valid = false;
        }
        if (valid) ans++;
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