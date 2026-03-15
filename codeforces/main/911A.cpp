#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m = INF;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        m = min(m, a[i]);
    }
    vector<ll> pos;
    for (ll i = 0; i < n; i++) {
        if (a[i] == m) pos.push_back(i);
    }
    ll ans = INF;
    for (ll i = 0; i < pos.size() - 1; i++) {
        ans = min(ans, pos[i + 1] - pos[i]);
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}