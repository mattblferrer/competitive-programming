#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<vector<ll>> adj;
vector<ll> dp, id;
map<pll, ll> mp;
vector<bool> seen;

void dfs(int u) {
    seen[u] = true;
    for (int v : adj[u]) {
        if (seen[v]) continue;
        if (mp[{u, v}] >= id[u]) dp[v] = dp[u];
        else dp[v] = dp[u] + 1;
        id[v] = mp[{u, v}];
        dfs(v);
    }
}

void solve() {
    ll n;
    cin >> n;
    adj.assign(n + 1, vector<ll>());
    dp.assign(n + 1, INF);
    id.assign(n + 1, 0);
    seen.assign(n + 1, 0);

    for (ll i = 1; i <= n - 1; i++) {
        ll ui, vi;
        cin >> ui >> vi;
        adj[ui].push_back(vi);
        adj[vi].push_back(ui);
        mp[{ui, vi}] = mp[{vi, ui}] = i;
    }

    dp[1] = 1;
    dfs(1);
    ll ans = 0;
    for (ll i = 1; i <= n; i++) ans = max(ans, dp[i]);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}