#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
const long long INF = 2e18;

void dijkstra(ll start, std::vector<std::vector<pll>> adj_list, 
    std::vector<ll>& dist, std::vector<ll>& path) {
    int n = adj_list.size();
    dist.resize(n, INF);
    path.resize(n, -1);
    std::priority_queue<pll, std::vector<pll>, std::greater<pll>> q;

    dist[start] = 0;  // starting vertex
    q.push({0, start});
    while (!q.empty()) {
        pll u = q.top();
        ll d_f = u.first;
        ll f = u.second;
        q.pop();

        if (d_f != dist[f]) continue;
        for (auto edge: adj_list[f]) {
            ll length = edge.first;
            ll v = edge.second;
            
            if (dist[f] + length < dist[v]) {
                dist[v] = dist[f] + length;
                path[v] = f;
                q.push({dist[v], v});
            }
        }
    }
}