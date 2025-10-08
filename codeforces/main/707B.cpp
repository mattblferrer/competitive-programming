#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct edge {
    ll u, v, l;
};

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<edge> edges(m);
    for (ll i = 0; i < m; i++) {
        ll u, v, l;
        cin >> u >> v >> l;
        edges[i] = {u, v, l};
    }
    set<ll> a;
    for (ll i = 0; i < k; i++) {
        ll a_i;
        cin >> a_i;
        a.insert(a_i);
    }
    sort(edges.begin(), edges.end(), [](edge a, edge b){
        return a.l < b.l;
    });
    ll ans = INF;
    for (edge e: edges) {
        if (a.count(e.u) ^ a.count(e.v)) ans = min(ans, e.l);
    }
    if (ans == INF) cout << -1;
    else cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}