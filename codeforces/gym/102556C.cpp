#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<set<ll>> adj(n);
    for (ll i = 0; i < n - 1; i++) {
        adj[i].insert(i + 1);
    }
    for (ll i = 1; i < n; i++) {
        adj[i].insert(i - 1);
    }
    for (ll i = 0; i < b; i++) {
        ll x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].clear();
        adj[x].insert(y);
    }
    vector<bool> seen(n);
    queue<ll> q;
    q.push(0);
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v: adj[u]) {
            if (seen[v]) continue;
            q.push(v);
        }
        seen[u] = true;
    }
    if (seen[a - 1]) cout << "YES\n";
    else cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}