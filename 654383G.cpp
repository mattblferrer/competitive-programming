#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;

struct store {
    ll dist, i;
    long double p;
};

const long long INF = 2e18;

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
    ll n, m, k, u, v, l;
    cin >> n >> m >> k;
    vector<vector<pll>> adj_list(n);
    for (ll i = 0; i < m; i++) {
        cin >> u >> v >> l;
        adj_list[u - 1].push_back({l, v - 1});
        adj_list[v - 1].push_back({l, u - 1});
    }
    long double p;
    vector<long double> prob(n);
    bool possible = false;
    for (ll i = 0; i < k; i++) {
        cin >> u >> p;
        prob[u - 1] = p;
        if (p == 1) possible = true;
    }
    if (!possible) { 
        cout << "impossible";
        return;
    }
    vector<ll> start, end, path;
    dijkstra(0, adj_list, start, path);
    dijkstra(n - 1, adj_list, end, path);
    vector<store> stores;
    for (int i = 0; i < n; i++) {
        if (prob[i] > 0) stores.push_back({start[i] + end[i], i, prob[i]});
    }   
    sort(stores.begin(), stores.end(), [](store a, store b) {
        return a.dist < b.dist;
    });

    long double ans = 0, prev = 1;
    for (store s: stores) {
        ans += s.p * prev * s.dist;
        prev *= (1 - s.p);
    }
    cout << setprecision(10) << ans;
    return;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}