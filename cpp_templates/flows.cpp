#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

struct flow {
    ll fs;  // flow size
    vector<set<ll>> adj;  // adjacency of every vertex i
    vector<vector<ll>> cap;  // residual capacity
    vector<vector<ll>> fg;  // flow graph (actual)

    ll bfs(ll s, ll t, vector<ll>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = s;
        queue<pll> q;
        q.push({s, INF});

        while (!q.empty()) { 
            ll curr = q.front().first, f = q.front().second;
            q.pop();
            for (ll next: adj[curr]) {
                if (parent[next] == -1 && cap[curr][next]) {
                    parent[next] = curr;
                    ll nf = min(f, cap[curr][next]);
                    if (next == t) return nf;
                    q.push({next, nf});
                }
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll f = 0, nf;
        vector<ll> parent(fs);

        while ((nf = bfs(s, t, parent))) {
            f += nf;
            ll curr = t;
            while (curr != s) {
                ll prev = parent[curr];
                cap[prev][curr] -= nf;
                cap[curr][prev] += nf;
                fg[prev][curr] += nf;
                fg[curr][prev] -= nf;
                curr = prev;
            }
        }
        return f;
    }

    void connect_d(ll u, ll v, ll w) {  // directed
        adj[u].insert(v);
        adj[v].insert(u);
        cap[u][v] += w;
    }

    void connect_u(ll u, ll v, ll w) {  // undirected
        adj[u].insert(v);
        adj[v].insert(u);
        cap[u][v] += w;
        cap[v][u] += w;
    }

    void resize_flow(ll sz) {
        fs = sz;
        adj.resize(sz);
        cap.resize(sz, vector<ll>(sz));
        fg.resize(sz, vector<ll>(sz));
    }
};
