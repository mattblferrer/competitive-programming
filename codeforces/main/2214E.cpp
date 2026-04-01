#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<vector<ll>> floyd_warshall(vector<vector<ll>> adj) {
    ll n = adj.size();
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j]) dist[i][j] = adj[i][j];
        }
    }
    for (ll i = 0; i < n; i++) {
        for (ll k = 0; k < n; k++) {
            for (ll j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1));
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }
    vector<vector<ll>> dist;
    dist = floyd_warshall(adj);
    for (ll i = 2; i <= n; i++) {
        if (dist[1][i] < INF) cout << dist[1][i] << "\n";
        else cout << "-1\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}