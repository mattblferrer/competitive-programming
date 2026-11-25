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

// minimum spanning forest (Kruskal), edges are {w, u, v}; returns {total weight, indices of the chosen edges}, O(E log E)
pair<ll, vector<int>> kruskal(int n, const vector<array<ll, 3>> &edges) {
    vector<int> p(n), order(edges.size()), chosen;
    iota(p.begin(), p.end(), 0);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return edges[a] < edges[b]; });
    auto find_set = [&](int x) {  // path halving, no recursion
        while (p[x] != x) x = p[x] = p[p[x]];
        return x;
    };
    ll total = 0;
    for (int i : order) {
        int u = find_set(edges[i][1]), v = find_set(edges[i][2]);
        if (u == v) continue;
        p[u] = v;
        total += edges[i][0];
        chosen.push_back(i);
    }
    return {total, chosen};
}

// at most 4n candidate edges {w, i, j} (w = Manhattan distance) that contain a Manhattan MST of the points
// (x[i], y[i]); kruskal(n, manhattan_mst_edges(x, y)) gives the MST. For each point, the nearest point in each
// of the 8 octants around it suffices; each pass sweeps one octant (then the points are reflected), O(n log n)
vector<array<ll, 3>> manhattan_mst_edges(vector<ll> x, vector<ll> y) {
    int n = x.size();
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    vector<array<ll, 3>> edges;
    for (int pass = 0; pass < 4; pass++) {
        sort(id.begin(), id.end(), [&](int i, int j) { return x[i] + y[i] < x[j] + y[j]; });
        map<ll, int> open;  // -y -> point still waiting for its nearest neighbour in this octant
        for (int i : id) {
            for (auto it = open.lower_bound(-y[i]); it != open.end(); it = open.erase(it)) {
                int j = it->second;
                ll dx = x[i] - x[j], dy = y[i] - y[j];
                if (dy > dx) break;
                edges.push_back({dx + dy, i, j});
            }
            open[-y[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            if (pass % 2) x[i] = -x[i];
            else swap(x[i], y[i]);
        }
    }
    return edges;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> x(n), y(n);
    for (ll i = 0; i < n; i++) cin >> x[i] >> y[i];
    vector<array<ll, 3>> edges = manhattan_mst_edges(x, y);
    auto [w, chosen] = kruskal(n, edges);
    cout << w << "\n";
    for (ll i = 0; i < chosen.size(); i++) cout << edges[chosen[i]][1] << " " << edges[chosen[i]][2] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
