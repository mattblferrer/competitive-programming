#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// Kahn's algorithm, O(V + E); returns vertices in topological order,
// or an empty vector if the graph has a cycle
vector<int> topo_sort(const vector<vector<int>> &adj_list) {
    int n = adj_list.size();
    vector<int> indeg(n), order;
    for (auto &edges : adj_list) {
        for (int v : edges) indeg[v]++;
    }
    for (int u = 0; u < n; u++) {
        if (!indeg[u]) order.push_back(u);
    }
    for (int i = 0; i < (int)order.size(); i++) {
        for (int v : adj_list[order[i]]) {
            if (--indeg[v] == 0) order.push_back(v);
        }
    }
    if ((int)order.size() < n) return {};
    return order;
}
