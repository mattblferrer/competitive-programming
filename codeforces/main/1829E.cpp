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
    vector<vector<ll>> a(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> a[i][j];
    }
    
    vector<ll> rd = {1, 0, -1, 0}, cd = {0, 1, 0, -1};
    parent.resize(n * m);
    sz.resize(n * m);
    for (ll i = 0; i < n * m; i++) make_set(i);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            for (ll k = 0; k < 4; k++) {
                ll r = i + rd[k], c = j + cd[k];
                if (r < 0 || r >= n || c < 0 || c >= m) continue;
                if (a[r][c] == 0 || a[i][j] == 0) continue;
                union_sets(r * m + c, i * m + j);
            }
        }
    }
    map<ll, ll> lakes;
    for (ll i = 0; i < n * m; i++) lakes[find_set(i)] += a[i / m][i % m];
    ll ans = 0;
    for (const auto& pair: lakes) {
        ll vol = pair.second;
        ans = max(ans, vol);
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}