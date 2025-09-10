#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

const long long INF = 2e18;
long long fs;  // flow size
std::vector<std::set<long long>> adj;  // adjacency of every vertex i
std::vector<std::vector<long long>> capacity;  // residual capacity
std::vector<std::vector<long long>> fg;  // flow graph (actual)

long long bfs(long long s, long long t, std::vector<long long>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    std::queue<std::pair<long long, long long>> q;
    q.push({s, INF});

    while (!q.empty()) { 
        long long curr = q.front().first, flow = q.front().second;
        q.pop();
        for (long long next: adj[curr]) {
            if (parent[next] == -1 && capacity[curr][next]) {
                parent[next] = curr;
                long long new_flow = std::min(flow, capacity[curr][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

long long max_flow(long long s, long long t) {
    long long flow = 0, new_flow;
    std::vector<long long> parent(fs);

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        long long curr = t;
        while (curr != s) {
            long long prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            fg[prev][curr] += new_flow;
            fg[curr][prev] -= new_flow;
            curr = prev;
        }
    }
    return flow;
}

void connect_d(long long u, long long v, long long w) {  // directed
    adj[u].insert(v);
    adj[v].insert(u);
    capacity[u][v] = w;
}

void connect_u(long long u, long long v, long long w) {  // undirected
    adj[u].insert(v);
    adj[v].insert(u);
    capacity[u][v] = w;
    capacity[v][u] = w;
}

void resize_flow(long long size) {
    fs = size;
    adj.resize(size);
    capacity.resize(size, std::vector<long long>(size));
    fg.resize(size, std::vector<long long>(size));
}

ll ABC205F() {
    ll h, w, n, a, b, c, d;
    std::cin >> h >> w >> n;
    for (ll i = 1; i <= n; i++) {
        std::cin >> a >> b >> c >> d;
    }
    // TODO: solve
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC205F() << "\n";
    return 0;
}