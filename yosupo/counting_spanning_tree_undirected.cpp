// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

// determinant of a square matrix mod a prime, O(n^3)
ll det_mod(vector<vector<ll>> a, ll p) {
    int n = a.size();
    ll det = 1;
    for (int c = 0; c < n; c++) {
        int r = c;
        while (r < n && a[r][c] % p == 0) r++;
        if (r == n) return 0;
        if (r != c) {
            swap(a[r], a[c]);
            det = (p - det) % p;
        }
        det = det * ((a[c][c] % p + p) % p) % p;
        ll inv = binexp((a[c][c] % p + p) % p, p - 2, p);
        for (int i = c + 1; i < n; i++) {
            ll f = (a[i][c] % p + p) % p * inv % p;
            if (f == 0) continue;
            for (int j = c; j < n; j++) a[i][j] = ((a[i][j] - f * ((a[c][j] % p + p) % p)) % p + p) % p;
        }
    }
    return det;
}

// number of spanning trees of a multigraph mod a prime (Kirchhoff), O(n^3); edges are {u, v}, self-loops are ignored
ll count_spanning_trees(int n, const vector<pair<int, int>> &edges, ll p) {
    if (n == 1) return 1 % p;
    vector<vector<ll>> lap(n, vector<ll>(n, 0));
    for (auto [u, v] : edges) {
        if (u == v) continue;
        lap[u][u]++;
        lap[v][v]++;
        lap[u][v]--;
        lap[v][u]--;
    }
    lap.pop_back();
    for (auto &row : lap) row.pop_back();
    return det_mod(lap, p);
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (ll i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    cout << count_spanning_trees(n, edges, MOD) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
