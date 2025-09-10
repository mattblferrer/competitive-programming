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

void problem546E() {
    ll n, m, p, q;
    std::cin >> n >> m;
    fs = 2*n + 2;
    adj.resize(fs);
    capacity.resize(fs, std::vector<long long>(fs));
    fg.resize(fs, std::vector<long long>(fs));
    
    std::vector<ll> a(n + 1), b(n + 1);
    for (ll i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (ll i = 1; i <= n; i++) {
        std::cin >> b[i];
    }
    for (ll i = 1; i <= m; i++) {
        std::cin >> p >> q;
        connect_d(p, n + q, a[p]);
        connect_d(q, n + p, a[q]);
    }
    for (ll i = 1; i <= n; i++) {
        connect_d(0, i, a[i]);
        connect_d(i, n + i, a[i]);
        connect_d(n + i, 2*n + 1, b[i]);
    }
    ll f = max_flow(0, 2*n + 1);
    ll a_sum = std::accumulate(a.begin(), a.end(), 0);
    ll b_sum = std::accumulate(b.begin(), b.end(), 0);
    if (a_sum != b_sum) {
        std::cout << "NO\n";
        return;
    }
    if (f != a_sum) {
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            std::cout << fg[i][n + j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem546E();
    return 0;
}