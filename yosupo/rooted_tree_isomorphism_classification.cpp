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

// tree isomorphism by canonical ids (AHU); compare ids from the same TreeCanon object
//   rooted(adj, root)   ids of the subtree of every vertex when rooted at root (the tree's id is [root]):
//                       equal ids means isomorphic, and ids are 0..ids.size()-1 in order of first appearance, O(n log n)
//   centers(adj)        the 1 or 2 centers of the tree, O(n)
//   unrooted(adj)       id of the unrooted tree: equal ids means isomorphic, O(n log n)
struct TreeCanon {
    map<vector<int>, int> ids;

    vector<int> rooted(const vector<vector<int>> &adj, int root) {
        int n = adj.size();
        vector<int> order{root}, par(n, -1), id(n);
        for (int i = 0; i < (int)order.size(); i++) {
            for (int v : adj[order[i]]) {
                if (v == par[order[i]]) continue;
                par[v] = order[i];
                order.push_back(v);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            vector<int> kids;
            for (int v : adj[u]) if (v != par[u]) kids.push_back(id[v]);
            sort(kids.begin(), kids.end());
            id[u] = ids.try_emplace(kids, ids.size()).first->second;
        }
        return id;
    }

    vector<int> centers(const vector<vector<int>> &adj) {
        int n = adj.size(), left = n;
        if (n <= 2) {
            vector<int> c(n);
            iota(c.begin(), c.end(), 0);
            return c;
        }
        vector<int> deg(n), layer;
        for (int u = 0; u < n; u++) {
            deg[u] = adj[u].size();
            if (deg[u] == 1) layer.push_back(u);
        }
        while (left > 2) {
            left -= layer.size();
            vector<int> next;
            for (int u : layer) for (int v : adj[u]) if (--deg[v] == 1) next.push_back(v);
            layer = next;
        }
        return layer;
    }

    int unrooted(const vector<vector<int>> &adj) {
        int res = INT_MAX;
        for (int c : centers(adj)) res = min(res, rooted(adj, c)[c]);
        return res;
    }
};

void solve() {
    ll n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (ll i = 1; i < n; i++) {
        ll p;
        cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    TreeCanon tc;
    vector<int> id = tc.rooted(adj, 0);
    cout << tc.ids.size() << "\n";
    for (ll i = 0; i < n; i++) cout << id[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
