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

// calls f(a, b, c) once for every triangle (three mutually adjacent vertices) of a simple undirected graph
// each edge is directed from the endpoint with the smaller (degree, id) to the other, so every vertex has
// O(sqrt E) out-edges; a triangle is found once, from its smallest vertex, O(E sqrt E)
template <class F>
void enumerate_triangles(int n, const vector<pair<int, int>> &edges, F f) {
    vector<int> deg(n), mark(n, -1);
    for (auto [u, v] : edges) deg[u]++, deg[v]++;
    vector<vector<int>> out(n);
    for (auto [u, v] : edges) {
        if (pair(deg[u], u) > pair(deg[v], v)) swap(u, v);
        out[u].push_back(v);
    }
    for (int a = 0; a < n; a++) {
        for (int b : out[a]) mark[b] = a;
        for (int b : out[a])
            for (int c : out[b]) if (mark[c] == a) f(a, b, c);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> x(n);
    for (ll i = 0; i < n; i++) cin >> x[i];
    vector<pair<int, int>> edges(m);
    for (ll i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    ll ans = 0;
    enumerate_triangles(n, edges, [&](int a, int b, int c) {
        ans = (ans + x[a] * x[b] % MOD * x[c]) % MOD;
        });
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
