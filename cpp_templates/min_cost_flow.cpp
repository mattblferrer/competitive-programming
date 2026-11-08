#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// min cost max flow (successive shortest paths with potentials); negative costs are fine, negative cycles are not
// after run: e[id].f is the flow on edge id (returned by connect)
// F = total flow pushed
//   MinCostFlow(n)            empty network on n vertices (0-indexed), O(n)
//   connect(u, v, cap, cost)  add directed edge u -> v, returns edge id, O(1)
//   init_potentials(s)        Bellman-Ford from s, only needed when some cost is negative, O(VE)
//   dijkstra(s)               shortest paths in reduced costs, O(E log V)
//   run(s, t, limit)          push up to limit units from s to t, returns {flow, cost}, O(F E log V) (+ O(VE) if costs are negative)
struct MinCostFlow {
    struct Edge { int to; ll cap, f, cost; };
    int n;
    vector<Edge> e;  // e[id ^ 1] is the reverse edge of e[id]
    vector<vector<int>> adj;
    vector<ll> pot, dist;
    vector<int> par;

    MinCostFlow(int n = 0): n(n), adj(n), pot(n, 0), dist(n), par(n) {}

    int connect(int u, int v, ll cap, ll cost) {
        adj[u].push_back(e.size());
        e.push_back({v, cap, 0, cost});
        adj[v].push_back(e.size());
        e.push_back({u, 0, 0, -cost});
        return e.size() - 2;
    }

    void init_potentials(int s) {
        fill(pot.begin(), pot.end(), INF);
        pot[s] = 0;
        for (int it = 0; it < n; it++) {
            bool changed = false;
            for (int u = 0; u < n; u++) {
                if (pot[u] == INF) continue;
                for (int id : adj[u]) {
                    if (e[id].cap > e[id].f && pot[u] + e[id].cost < pot[e[id].to]) {
                        pot[e[id].to] = pot[u] + e[id].cost;
                        changed = true;
                    }
                }
            }
            if (!changed) break;
        }
    }

    bool dijkstra(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(par.begin(), par.end(), -1);
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (int id : adj[u]) {
                int v = e[id].to;
                if (e[id].cap <= e[id].f || pot[v] == INF) continue;
                ll nd = d + e[id].cost + pot[u] - pot[v];
                if (nd < dist[v]) {
                    dist[v] = nd;
                    par[v] = id;
                    pq.push({nd, v});
                }
            }
        }
        return dist[t] != INF;
    }

    pll run(int s, int t, ll limit = INF) {
        for (auto &ed : e) {
            if (ed.cost < 0 && ed.cap > 0) {
                init_potentials(s);
                break;
            }
        }
        ll flow = 0, cost = 0;
        while (flow < limit && dijkstra(s, t)) {
            for (int u = 0; u < n; u++) if (dist[u] < INF) pot[u] += dist[u];
            ll f = limit - flow;
            for (int v = t; v != s; v = e[par[v] ^ 1].to) f = min(f, e[par[v]].cap - e[par[v]].f);
            for (int v = t; v != s; v = e[par[v] ^ 1].to) {
                e[par[v]].f += f;
                e[par[v] ^ 1].f -= f;
            }
            flow += f;
            cost += f * (pot[t] - pot[s]);
        }
        return {flow, cost};
    }
};
