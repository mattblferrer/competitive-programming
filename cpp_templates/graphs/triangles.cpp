// Contents
//   enumerate_triangles  calls f(a, b, c) once for every triangle of a simple undirected graph, O(E sqrt E)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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
