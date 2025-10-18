#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

void bellman_ford(ll start, ll n, vector<vector<ll>> edges,
    vector<ll>& dist) {
    dist.resize(n, INF);
    dist[start] = 0;
    for (ll i = 0; i < n - 1; i++) {
        for (auto e: edges) {
            dist[e[1]] = min(dist[e[1]], dist[e[0]] + e[2]);
        }
    }
}

vector<vector<ll>> floyd_warshall(vector<vector<ll>> adj) {
    ll n = adj.size();
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j]) dist[i][j] = adj[i][j];
        }
    }
    for (ll k = 0; k < n; k++) {
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

void dijkstra(ll start, vector<vector<pll>> adj_list, 
    vector<ll>& dist, vector<ll>& path) {
    int n = adj_list.size();
    dist.resize(n, INF);
    path.resize(n, -1);
    priority_queue<pll, vector<pll>, greater<pll>> q;

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