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

// diameter of a tree with edge weights >= 0, 0-indexed; adj[u] = {v, w}, use w = 1 for unweighted
// returns {length, path}, path = the vertices from one end of the diameter to the other, O(n)
pair<ll, vector<int>> tree_diameter(const vector<vector<pair<int, ll>>> &adj) {
    int n = adj.size();
    vector<int> par(n);
    vector<ll> dist(n);
    auto farthest = [&](int s) {  // fills par and dist from s, returns the vertex farthest from s
        fill(par.begin(), par.end(), -1);
        dist[s] = 0;
        vector<int> stk{s};
        int best = s;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            if (dist[u] > dist[best]) best = u;
            for (auto [v, w] : adj[u]) {
                if (v == par[u]) continue;
                par[v] = u, dist[v] = dist[u] + w;
                stk.push_back(v);
            }
        }
        return best;
        };
    int b = farthest(farthest(0));
    vector<int> path;
    for (int v = b; v != -1; v = par[v]) path.push_back(v);
    return {dist[b], path};
}

void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    auto [len, path] = tree_diameter(adj);
    cout << len << " " << path.size() << "\n";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << "\n";
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
