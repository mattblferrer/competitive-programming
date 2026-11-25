// Contents
//   SumDist         rerooting DP example: sum of distances from each vertex to all others
//   rerooting       answer of a tree DP for every choice of root; returns ans[v] for each v
//   MaxDist         rerooting example: distance to the farthest vertex, weighted edges (merge with no inverse)
//   PathComposite   rerooting example: sum over all paths of edge maps b x + c applied to vertex values

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// rerooting DP example: sum of distances from each vertex to all others, T = {sum of distances, vertex count}
// id = empty merge, merge combines children (need not be invertible), lift moves a value across edge from -> to,
// finish adds vertex v to the merged children; use from and to to look up edge weights
// the functions can be static (as here) or const members of a spec object passed to rerooting, which can then
// hold the data they need, such as vertex values or edge weights
struct SumDist {
    using T = pll;
    static T id() { return {0, 0}; }
    static T merge(const T &a, const T &b) { return {a.first + b.first, a.second + b.second}; }
    static T lift(const T &x, int, int) { return {x.first + x.second, x.second}; }
    static T finish(const T &x, int) { return {x.first, x.second + 1}; }
};

// answer of a tree DP for every choice of root; returns ans[v] for each v, O(n)
// s is a spec shaped like SumDist above: rerooting<SumDist>(adj) for static specs, rerooting(adj, s) to pass one
template <class S>
vector<typename S::T> rerooting(const vector<vector<int>> &adj, const S &s = S()) {
    using T = typename S::T;
    int n = adj.size();
    vector<int> order{0}, par(n, -1);
    for (int i = 0; i < (int)order.size(); i++) {
        for (int v : adj[order[i]]) {
            if (v == par[order[i]]) continue;
            par[v] = order[i];
            order.push_back(v);
        }
    }
    vector<T> down(n, s.id()), up(n, s.id()), ans(n);  // up[v] = what v's parent contributes to v
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        T cur = s.id();
        for (int u : adj[v]) if (u != par[v]) cur = s.merge(cur, s.lift(down[u], u, v));
        down[v] = s.finish(cur, v);
    }
    for (int v : order) {
        int k = adj[v].size();
        vector<T> pre(k + 1, s.id()), suf(k + 1, s.id());  // allows merge to have no inverse
        auto value = [&](int u) { return u == par[v] ? up[v] : s.lift(down[u], u, v); };
        for (int i = 0; i < k; i++) pre[i + 1] = s.merge(pre[i], value(adj[v][i]));
        for (int i = k - 1; i >= 0; i--) suf[i] = s.merge(value(adj[v][i]), suf[i + 1]);
        ans[v] = s.finish(pre[k], v);
        for (int i = 0; i < k; i++) {
            int u = adj[v][i];
            if (u != par[v]) up[u] = s.lift(s.finish(s.merge(pre[i], suf[i + 1]), v), v, u);
        }
    }
    return ans;
}

// rerooting example: distance from each vertex to the farthest vertex, with edge weights; T = farthest distance.
// merge is max, which has no inverse; the weights live in the spec object: rerooting(adj, MaxDist{w})
struct MaxDist {
    using T = ll;
    map<pair<int, int>, ll> w;  // weight of each edge, keyed by its endpoints {min, max}

    T id() const { return LLONG_MIN; }
    T merge(const T &a, const T &b) const { return max(a, b); }
    T lift(const T &x, int from, int to) const { return x + w.at({min(from, to), max(from, to)}); }
    T finish(const T &x, int) const { return max(x, 0LL); }
};

// rerooting example: each edge e is a map f_e(x) = b x + c mod `mod` and each vertex v has a value a[v];
// for every x, the sum over all y of f along the path from x to y applied to a[y] (the edge nearest y first)
// T = {sum of the values reaching this side's top vertex, number of vertices on this side}
struct PathComposite {
    using T = pll;
    ll mod = 998'244'353;
    vector<ll> val;
    map<pair<int, int>, pll> edge;  // {b, c} of each edge, keyed by its endpoints {min, max}

    T id() const { return {0, 0}; }
    T merge(const T &a, const T &b) const { return {(a.first + b.first) % mod, a.second + b.second}; }
    T lift(const T &x, int from, int to) const {
        auto [b, c] = edge.at({min(from, to), max(from, to)});
        return {(b * x.first + c * x.second) % mod, x.second};
    }
    T finish(const T &x, int v) const { return {(x.first + val[v]) % mod, x.second + 1}; }
};
