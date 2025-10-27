#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_valid(vector<vector<ll>> adj_list, ll k) {
    set<pll> edges;
    ll n = adj_list.size();
    vector<vector<bool>> seen(n, vector<bool>(n));
    for (ll i = 0; i < n; i++) seen[i][i] = true;
    ll p = n;

    for (ll i = 0; i < n; i++) {
        for (ll j: adj_list[i]) {
            seen[i][j] = seen[j][i] = true;
            p++;
        }
        for (ll j = i + 1; j < n; j++) edges.insert({i, j});
    }

    ll old_p = -1;
    while (old_p != p) {
        old_p = p;
        for (auto it = edges.begin(); it != edges.end(); it++) {
            auto e = *it;
            ll a = e.first, b = e.second;
            ll sd = adj_list[a].size() + adj_list[b].size(); 
            if (seen[a][b]) continue;
            if (sd >= k) {
                seen[a][b] = seen[b][a] = true;
                adj_list[a].push_back(b);
                adj_list[b].push_back(a);
                p += 2;
            }
        }
    }
    if (p == n * n) return true;
    else return false;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj_list(n);
    for (ll i = 0; i < m; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        ai--; bi--;
        adj_list[ai].push_back(bi);
        adj_list[bi].push_back(ai);
    }

    ll left = -1, right = n * 2;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        if (!is_valid(adj_list, mid)) right = mid; 
        else left = mid; 
    }
    cout << left;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}