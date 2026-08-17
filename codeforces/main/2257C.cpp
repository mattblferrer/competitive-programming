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
    vector<ll> p(n + 1);
    vector<vector<ll>> adj(n + 1);
    for (ll i = 2; i <= n; i++) {
        cin >> p[i];
        adj[i].push_back(p[i]);
        adj[p[i]].push_back(i);
    }
    ll m;
    cin >> m;
    vector<ll> a(m + 1);
    for (ll i = 1; i <= m; i++) cin >> a[i];
    set<ll> a_set(a.begin(), a.end());

    vector<ll> ans;
    vector<ll> d(n + 1, -1);
    queue<ll> q;
    q.push(1);
    d[1] = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        if (a_set.count(u)) ans.push_back(u);
        for (ll v : adj[u]) {
            if (d[v] != -1) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }

    sort(ans.begin() + 1, ans.end());
    cout << ans.size() - 1 << " ";
    for (ll i = 1; i < ans.size(); i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}