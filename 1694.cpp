#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
const ll INF = 2e18;

long long flow_size;
std::vector<std::set<long long>> adj;
std::vector<std::vector<long long>> capacity;

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
    std::vector<long long> parent(flow_size + 1);

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        long long curr = t;
        while (curr != s) {
            long long prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            curr = prev;
        }
    }
    return flow;
}

ll CSES1694() {
    ll n, m, a, b, c;
    std::cin >> n >> m;
    adj.resize(n + 1);
    capacity.resize(n + 1);
    flow_size = n;
    for (ll i = 1; i <= n; i++) {
        capacity[i].resize(n + 1);
    }
    for (ll i = 1; i <= m; i++) {
        std::cin >> a >> b >> c;
        adj[a].insert(b);
        adj[b].insert(a);
        capacity[a][b] += c; 
    }
    return max_flow(1, n);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1694() << "\n";
    return 0;
}