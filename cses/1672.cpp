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
    for (ll k = 0; k < n; k++) {
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < n; j++) {
                if ((dist[i][k] >= INF) || (dist[k][j] >= INF)) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> adj(n, vector<ll>(n));
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        if (adj[a][b] == 0) adj[a][b] = adj[b][a] = c;
        else adj[a][b] = adj[b][a] = min(adj[a][b], c);
    }

    vector<vector<ll>> dist;
    dist = floyd_warshall(adj);
    for (ll i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        if (dist[a][b] != INF) cout << dist[a][b] << "\n";
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