#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

const long long INF = 2e18;
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

void CSES1696() {
    ll n, m, k, a, b;
    std::cin >> n >> m >> k;
    flow_size = n + m + 2;
    adj.resize(flow_size + 1);
    capacity.resize(flow_size + 1);
    for (ll i = 0; i <= flow_size; i++) {
        capacity[i].resize(flow_size + 1);
    }
    for (ll i = 1; i <= n; i++) {
        adj[0].insert(i);
        adj[i].insert(0);
        capacity[0][i] = 1;
    }
    for (ll i = n + 1; i <= n + m; i++) {
        adj[i].insert(n + m + 1);
        adj[n + m + 1].insert(i);
        capacity[i][n + m + 1] = 1;
    }
    for (ll i = 1; i <= k; i++) {
        std::cin >> a >> b;
        adj[a].insert(n + b);
        adj[n + b].insert(a);
        capacity[a][n + b] = 1;
    }
    std::cout << max_flow(0, n + m + 1) << "\n";
    for (ll i = 1; i <= n; i++) {
        for (ll j = n + 1; j <= n + m; j++) {
            if (capacity[j][i]) std::cout << i << " " << j - n << "\n";
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES1696();
    return 0;
}