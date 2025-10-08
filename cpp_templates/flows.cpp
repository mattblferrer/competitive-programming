#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

const ll INF = 2e18;
ll fs;  // flow size
vector<set<ll>> adj;  // adjacency of every vertex i
vector<vector<ll>> capacity;  // residual capacity
vector<vector<ll>> fg;  // flow graph (actual)

ll bfs(ll s, ll t, vector<ll>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    queue<pll> q;
    q.push({s, INF});

    while (!q.empty()) { 
        ll curr = q.front().first, flow = q.front().second;
        q.pop();
        for (ll next: adj[curr]) {
            if (parent[next] == -1 && capacity[curr][next]) {
                parent[next] = curr;
                ll new_flow = min(flow, capacity[curr][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

ll max_flow(ll s, ll t) {
    ll flow = 0, new_flow;
    vector<ll> parent(fs);

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        ll curr = t;
        while (curr != s) {
            ll prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            fg[prev][curr] += new_flow;
            fg[curr][prev] -= new_flow;
            curr = prev;
        }
    }
    return flow;
}

void connect_d(ll u, ll v, ll w) {  // directed
    adj[u].insert(v);
    adj[v].insert(u);
    capacity[u][v] += w;
}

void connect_u(ll u, ll v, ll w) {  // undirected
    adj[u].insert(v);
    adj[v].insert(u);
    capacity[u][v] += w;
    capacity[v][u] += w;
}

void resize_flow(ll size) {
    fs = size;
    adj.resize(size);
    capacity.resize(size, vector<ll>(size));
    fg.resize(size, vector<ll>(size));
}
