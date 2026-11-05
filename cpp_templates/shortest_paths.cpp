#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// single-source shortest paths, negative weights allowed
//   BellmanFord(start, n, edges)   edges: {u, v, w}; pass with move() to avoid copying, O(V)
//   run()                          relax all edges up to V times, O(VE)
//                                  returns true if a negative cycle is reachable from start
struct BellmanFord {
    ll start, n;
    vector<vector<ll>> edges;
    vector<ll> dist;

    BellmanFord(ll start, ll n, vector<vector<ll>> edges)
        : start(start), n(n), edges(move(edges)), dist(n, INF) {
        dist[start] = 0;
    }

    bool run() {
        for (ll i = 0; i < n; i++) {
            bool relaxed = false;
            for (auto &e : edges) {
                if (dist[e[0]] == INF) continue;  // unreachable
                if (dist[e[0]] + e[2] < dist[e[1]]) {
                    dist[e[1]] = dist[e[0]] + e[2];
                    relaxed = true;
                }
            }
            if (!relaxed) return false;  // converged early
        }
        return true;
    }
};

// all-pairs shortest paths; adj[i][j] = weight, 0 means no edge
//   FloydWarshall(adj)   stores adj, O(n^2)
//   run()                compute dist[i][j] for all pairs, O(n^3)
struct FloydWarshall {
    ll n;
    vector<vector<ll>> adj, dist;

    FloydWarshall(vector<vector<ll>> adj)
        : n(adj.size()), adj(move(adj)), dist(n, vector<ll>(n, INF)) {
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
                if (dist[i][k] == INF) continue;
                for (ll j = 0; j < n; j++) {
                    if (dist[k][j] == INF) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};

// single-source shortest paths, non-negative weights only
//   Dijkstra(start, adj_list)   adj_list[u] = {length, v}, O(V)
//   run()                       fill dist and path (parent of each vertex), O((V + E) log E)
//   has_path(end)               whether end is reachable from start, O(1)
struct Dijkstra {
    ll start, size;
    vector<vector<pll>> adj_list;
    vector<ll> dist, path;

    Dijkstra(ll start, vector<vector<pll>> adj_list)
        : start(start), size(adj_list.size()), adj_list(move(adj_list)), dist(size, INF), path(size, -1) {
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
            for (auto &edge : adj_list[f]) {
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
