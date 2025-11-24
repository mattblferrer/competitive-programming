#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct dsu {
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
};

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<dsu> d(m);
    for (ll i = 0; i < m; i++) {
        d[i].parent.resize(n);
        d[i].sz.resize(n);
    }
    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j < n; j++) {
            d[i].make_set(j);
        }
    }
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--; c--;
        d[c].union_sets(a, b);
    }
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        ll ans = 0;
        for (ll c = 0; c < m; c++) {
            if (d[c].is_connected(u, v)) ans++;
        }
        cout << ans << '\n';
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}