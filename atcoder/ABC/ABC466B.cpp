#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    map<ll, ll> max_size;
    for (ll i = 0; i < n; i++) {
        ll ci, si;
        cin >> ci >> si;
        max_size[ci] = max(max_size[ci], si);
    }
    for (ll i = 1; i <= m; i++) {
        if (max_size[i] == 0) cout << "-1 ";
        else cout << max_size[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}