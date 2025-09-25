#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void dijkstra(ll start, std::vector<std::vector<pll>> adj_list, 
    std::vector<ll>& dist, std::vector<ll>& path) {
    int n = adj_list.size();
    dist.resize(n, INF);
    path.resize(n, -1);
    std::priority_queue<pll, std::vector<pll>, std::greater<pll>> q;

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

void solve() {
    int n, m, a, b, c;
    cin >> n >> m;
    vector<vector<pll>> adj_list(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        a--; b--;
        adj_list[a].push_back({c, b});
    }
    vector<ll> dist, path;
    dijkstra(0, adj_list, dist, path);
    for (int i = 0; i < n; i++) {
        cout << dist[i] << " ";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}