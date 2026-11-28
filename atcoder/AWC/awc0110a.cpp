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
    vector<ll> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];
    for (ll i = 0; i < m; i++) {
        ll ti, vi;
        cin >> ti >> vi;
        s[ti - 1] = max(s[ti - 1] + vi, 0LL);
    }
    for (ll i = 0; i < n; i++) cout << s[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}