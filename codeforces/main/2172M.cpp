#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    vector<vector<ll>> adj_list(n);
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    vector<ll> distk(k);
    queue<ll> q;
    q.push(0);
    vector<ll> dist(n, INF);
    dist[0] = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v: adj_list[u]) {
            if (dist[v] != INF) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    for (ll i = 0; i < n; i++) {
        distk[a[i]] = max(distk[a[i]], dist[i]);
    }
    for (ll i = 0; i < k; i++) {
        cout << distk[i] << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    solve();
    return 0;
}