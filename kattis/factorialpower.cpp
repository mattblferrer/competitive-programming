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
    ll ans = 0;
    vector<pll> pf;
    for (ll i = 2; i * i <= n; i++) {
        ll cur_pow = 0;
        while (n % i == 0) {
            n /= i;
            cur_pow++;
        }
        if (cur_pow != 0) pf.push_back({i, cur_pow});
    }
    if (n != 1) pf.push_back({n, 1});

    ll curr = pf.back().first;
    while (curr <= m) {
        ans += m / curr;
        curr *= pf.back().first;
    }
    ans /= pf.back().second;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}