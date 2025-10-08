#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

void topo_sort(vector<vector<int>>& adj_list, vector<bool>& seen, 
    vector<int>& order, vector<bool>& curr, bool& cycle, int u) {
    if (seen[u]) return;
    if (curr[u]) {
        cycle = true;
        return;
    }
    curr[u] = true;
    for (int v: adj_list[u]) {
        topo_sort(adj_list, seen, order, curr, cycle, v);
    }
    seen[u] = true;
    order.push_back(u);
}