#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

map<pll, ll> mp;
vector<ll> x, sz;
set<pll> seen;

ll dfs_sz(ll u, ll parent, vector<vector<ll>> &adj) {
    ll curr = 1;
    for (ll v : adj[u]) {
        if (v != parent) curr += dfs_sz(v, u, adj);
    }
    sz[u] = curr;
    return curr;
}

void dfs_calc(ll n, ll u, ll parent, vector<vector<ll>> &adj) {
    for (ll v : adj[u]) {
        ll lo = min(u, v), hi = max(u, v);
        if (seen.count({lo, hi})) continue;
        if (v != parent) {
            if (sz[v] > n / 2) {
                x[v] += mp[{lo, hi}] + 1;
            }
            else {
                x[0] += mp[{lo, hi}] + 1;
                x[v] -= mp[{lo, hi}] + 1;
            }
            dfs_calc(n, v, u, adj);
            seen.insert({lo, hi});
        }
    }
}

void propagate(ll u, ll parent, vector<vector<ll>> &adj) {
    for (ll v : adj[u]) {
        if (v != parent) {
            x[v] = x[u] + x[v];
            propagate(v, u, adj);
        }
    }
}

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < n - 1; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        ai--; bi--;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
        mp[{ai, bi}] = i;
    }
    x.assign(n, 0);
    sz.assign(n, 0);
    dfs_sz(0, -1, adj);
    dfs_calc(n, 0, -1, adj);
    propagate(0, -1, adj);
    for (ll i = 0; i < n; i++) cout << x[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}