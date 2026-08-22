#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n + 1);
    for (ll i = 0; i < m; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
    }

    queue<ll> q;
    q.push(1);
    vector<ll> dist(n + 1, -1), prev(n + 1);
    dist[1] = 0;

    bool has_cycle = false;
    ll s1, s2;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v : adj[u]) {
            if (dist[v] != -1) {
                if (dist[u] == dist[v]) {
                    has_cycle = true;
                    s1 = u;
                    s2 = v;
                }
                continue;
            }
            dist[v] = dist[u] + 1;
            prev[v] = u;
            q.push(v);
        }
    }
    if (!has_cycle) { cout << "-1\n"; return; }


    deque<ll> cycle;
    while (s1 != s2) {
        cycle.push_front(s1);
        cycle.push_back(s2);
        s1 = prev[s1];
        s2 = prev[s2];
    }
    cycle.push_back(s1);

    cout << cycle.size() << " ";
    for (ll vi : cycle) cout << vi << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}