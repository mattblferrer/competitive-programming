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

// bridges, articulation points and biconnected components of an undirected graph; multi-edges are handled correctly
//   Biconnected(n)        empty graph on n vertices, O(n)
//   add_edge(u, v)        add the undirected edge u - v, returns its id, O(1)
//   dfs(root)             visit the component of root (iterative, so deep graphs can't overflow the stack), O(V + E) total
//   run()                 fills is_bridge[id], artics, and blocks (vertex lists), O(V + E)
//   block_cut_tree(node)  tree whose nodes are the artics then the blocks; node[u] is u's tree node (-1 if isolated), O(V + E)
//   bridge_tree(comp)     tree of 2-edge-connected components; comp[u] is u's tree node, O(V + E)
struct Biconnected {
    int n, m = 0, timer = 0;
    vector<vector<pair<int, int>>> adj;  // {to, edge id}
    vector<int> disc, low, stk, artics;
    vector<vector<int>> blocks;
    vector<char> is_bridge;
    vector<pair<int, int>> edges;

    Biconnected(int n = 0): n(n), adj(n) {}

    int add_edge(int u, int v) {
        adj[u].push_back({v, m});
        adj[v].push_back({u, m});
        edges.push_back({u, v});
        return m++;
    }

    void dfs(int root) {
        // frames {u, edge u was entered by (-1 for root), next index in adj[u], children v with disc[u] <= low[v]}
        // u is an articulation point if that count is >= 1 (>= 2 for the root, where every child counts)
        vector<array<int, 4>> call;
        auto enter = [&](int u, int pe) {
            disc[u] = low[u] = timer++;
            stk.push_back(u);
            call.push_back({u, pe, 0, 0});
        };
        enter(root, -1);
        while (!call.empty()) {
            auto [u, pe, i, cuts] = call.back();
            if (i < (int)adj[u].size()) {
                call.back()[2]++;
                auto [v, id] = adj[u][i];
                if (id == pe) continue;
                if (disc[v] == -1) enter(v, id);
                else low[u] = min(low[u], disc[v]);
                continue;
            }
            call.pop_back();  // u is finished: return to its parent p through edge pe
            if (cuts >= (pe == -1 ? 2 : 1)) artics.push_back(u);
            if (pe == -1) continue;
            int p = call.back()[0];
            low[p] = min(low[p], low[u]);
            if (disc[p] < low[u]) is_bridge[pe] = true;
            if (disc[p] <= low[u]) {
                call.back()[3]++;
                blocks.push_back({p});
                int x;
                do {
                    x = stk.back();
                    stk.pop_back();
                    blocks.back().push_back(x);
                } while (x != u);
            }
        }
    }

    void run() {
        disc.assign(n, -1);
        low.assign(n, 0);
        is_bridge.assign(m, false);
        for (int u = 0; u < n; u++) {
            if (disc[u] == -1) {
                dfs(u);
                stk.clear();
            }
        }
    }

    vector<vector<int>> block_cut_tree(vector<int> &node) {
        int a = artics.size();
        vector<vector<int>> tree(a + blocks.size());
        node.assign(n, -1);
        vector<char> is_art(n, false);
        for (int i = 0; i < a; i++) {
            node[artics[i]] = i;
            is_art[artics[i]] = true;
        }
        for (int i = 0; i < (int)blocks.size(); i++) {
            for (int u : blocks[i]) {
                if (is_art[u]) {
                    tree[node[u]].push_back(a + i);
                    tree[a + i].push_back(node[u]);
                } else {
                    node[u] = a + i;
                }
            }
        }
        return tree;
    }

    vector<vector<int>> bridge_tree(vector<int> &comp) {
        comp.assign(n, -1);
        int c = 0;
        for (int s = 0; s < n; s++) {
            if (comp[s] != -1) continue;
            vector<int> st{s};
            comp[s] = c;
            while (!st.empty()) {
                int u = st.back();
                st.pop_back();
                for (auto [v, id] : adj[u]) {
                    if (!is_bridge[id] && comp[v] == -1) {
                        comp[v] = c;
                        st.push_back(v);
                    }
                }
            }
            c++;
        }
        vector<vector<int>> tree(c);
        for (int id = 0; id < m; id++) {
            if (!is_bridge[id]) continue;
            int a = comp[edges[id].first], b = comp[edges[id].second];
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        return tree;
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;
    Biconnected g(n);
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        g.add_edge(a, b);
    }
    g.run();
    vector<int> comp;
    vector<vector<int>> tree = g.bridge_tree(comp);
    vector<vector<ll>> groups(tree.size());
    for (ll u = 0; u < n; u++) groups[comp[u]].push_back(u);
    cout << groups.size() << "\n";
    for (ll c = 0; c < groups.size(); c++) {
        cout << groups[c].size() << " ";
        for (ll u : groups[c]) cout << u << " ";
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
