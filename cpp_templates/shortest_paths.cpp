#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
const long long INF = 2e18;

std::vector<ll> dijkstra(ll n, std::vector<std::vector<pll>> adj_list) {
    int n = adj_list.size();
    std::vector<ll> dist(n, INF);
    std::vector<ll> path(n, -1);
    std::priority_queue<pll, std::vector<pll>, std::greater<pll>> q;

    dist[0] = 0;  // starting vertex
    q.push({0, 0});
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
    return dist;
}