#include <bits/stdc++.h>

void topo_sort(std::vector<std::vector<int>>& adj_list, std::vector<bool>& seen, 
    std::vector<int>& order, std::vector<bool>& curr, bool& cycle, int u) {
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