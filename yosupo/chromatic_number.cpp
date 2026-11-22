// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// fewest colors for a proper vertex coloring (inclusion-exclusion over independent sets), O(2^n n) time, O(2^n) memory, n up to about 23
// checks two primes, so a wrong answer needs both to cancel by chance; edges are {u, v}, self-loops are ignored
int chromatic_number(int n, const vector<pair<int, int>> &edges) {
    if (n == 0) return 0;
    const ll M1 = 998'244'353, M2 = 1'000'000'007;
    vector<int> adj(n);
    for (auto [u, v] : edges) {
        if (u == v) continue;
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }
    int full = 1 << n;
    vector<int> ind(full, 1), g1(full, 1), g2(full, 1);  // ind[S] = number of independent subsets of S
    for (int s = 1; s < full; s++) {
        int v = __builtin_ctz(s), rest = s ^ (1 << v);
        ind[s] = ind[rest] + ind[rest & ~adj[v]];
    }
    for (int k = 1; k < n; k++) {  // g[S] = ways to choose k independent sets inside S, in order
        ll s1 = 0, s2 = 0;
        for (int s = 0; s < full; s++) {
            g1[s] = g1[s] * (ll)ind[s] % M1;
            g2[s] = g2[s] * (ll)ind[s] % M2;
            bool neg = (n - __builtin_popcount(s)) & 1;
            s1 += neg ? M1 - g1[s] : g1[s];
            s2 += neg ? M2 - g2[s] : g2[s];
        }
        if (s1 % M1 != 0 || s2 % M2 != 0) return k;
    }
    return n;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (ll i = 0; i < m; i++) {
        int ui, vi;
        cin >> ui >> vi;
        edges[i] = {ui, vi};
    }
    cout << chromatic_number(n, edges) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
