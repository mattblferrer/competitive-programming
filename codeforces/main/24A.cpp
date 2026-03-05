#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> edges(n, vector<ll>(3));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < 3; j++) cin >> edges[i][j];
    }
    map<ll, vector<pll>> adj;
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        ll ai = edges[i][0], bi = edges[i][1], ci = edges[i][2];
        sum += ci;
        adj[ai].push_back({bi, 0});
        adj[bi].push_back({ai, ci});
    }
    ll fi = 1, se, curr = 0;
    vector<bool> seen(n + 1);
    for (ll i = 0; i < n - 1; i++) {
        if (seen[adj[fi][0].first]) {
            se = adj[fi][1].first;
            curr += adj[fi][1].second;
        }
        else {
            se = adj[fi][0].first;
            curr += adj[fi][0].second;
        }
        seen[fi] = true;
        fi = se;
    }
    for (ll i = 0; i < 2; i++) {
        if (adj[se][i].first == 1) curr += adj[se][i].second;
    }
    cout << min(curr, sum - curr);
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}