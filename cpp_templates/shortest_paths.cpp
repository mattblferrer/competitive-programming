#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

struct bellman_ford {
    ll start, n;
    vector<vector<ll>> edges;
    vector<ll> dist;

    bellman_ford(ll start, ll n, vector<vector<ll>> edges) {
        this->start = start;
        this->n = n;
        this->edges = edges;
        dist.resize(n, INF);
        dist[start] = 0;
    }

    void run() {
        for (ll i = 0; i < n - 1; i++) {
            for (auto e : edges) {
                dist[e[1]] = min(dist[e[1]], dist[e[0]] + e[2]);
            }
        }
    }
};

struct floyd_warshall {
    ll n;
    vector<vector<ll>> adj, dist;

    floyd_warshall(vector<vector<ll>> adj) {
        this->adj = adj;
        this->n = adj.size();
        dist.resize(n, vector<ll>(n, INF));
    }

    void run() {
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
    }
};

struct dijkstra {
    ll start, size;
    vector<vector<pll>> adj_list;
    vector<ll> dist, path;

    dijkstra(ll start, vector<vector<pll>> adj_list) {
        this->start = start;
        this->adj_list = adj_list;
        this->size = adj_list.size();
        dist.resize(size, INF);
        path.resize(size, -1);
    }

    void run() {
        priority_queue<pll, vector<pll>, greater<pll>> q;
        dist[start] = 0;  // starting vertex
        q.push({0, start});
        while (!q.empty()) {
            pll u = q.top();
            ll d_f = u.first;
            ll f = u.second;
            q.pop();

            if (d_f != dist[f]) continue;
            for (auto edge : adj_list[f]) {
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

    bool has_path(ll end) {
        return !(dist[end] >= INF);
    }
};
