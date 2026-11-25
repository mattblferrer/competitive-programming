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

// connected components of the complement of a simple undirected graph, 0-indexed; BFS that only scans vertices not
// yet visited, keeping the ones adjacent to the current vertex for later (each kept vertex is paid for by an edge), O(n + m)
vector<vector<int>> complement_components(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> left(n), mark(n, -1);
    iota(left.begin(), left.end(), 0);
    vector<vector<int>> comps;
    while (!left.empty()) {
        vector<int> comp{left.back()};
        left.pop_back();
        for (size_t i = 0; i < comp.size(); i++) {
            int u = comp[i];
            for (int v : adj[u]) mark[v] = u;
            vector<int> keep;
            for (int v : left) (mark[v] == u ? keep : comp).push_back(v);
            left.swap(keep);
        }
        comps.push_back(comp);
    }
    return comps;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (ll i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<vector<int>> comps = complement_components(adj);
    cout << comps.size() << "\n";
    for (auto &c : comps) {
        cout << c.size();
        for (int v : c) cout << " " << v;
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
