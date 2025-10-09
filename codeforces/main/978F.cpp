#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> r(n), rsort(n);
    for (ll i = 0; i < n; i++) {
        cin >> r[i];
        rsort[i] = r[i];
    }
    sort(rsort.begin(), rsort.end());
    vector<vector<ll>> q(n);
    for (ll i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;
        x--; y--;
        q[x].push_back(r[y]);
        q[y].push_back(r[x]);
    }
    for (ll i = 0; i < n; i++) {
        sort(q[i].begin(), q[i].end());
    }
    for (ll i = 0; i < n; i++) {
        ll ans = distance(rsort.begin(), lower_bound(rsort.begin(), rsort.end(), r[i]));
        ans -= distance(q[i].begin(), lower_bound(q[i].begin(), q[i].end(), r[i]));
        cout << ans << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}