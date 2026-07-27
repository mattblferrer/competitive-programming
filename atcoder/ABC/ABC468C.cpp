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
    vector<ll> p(n), q(n);
    for (ll i = 0; i < n; i++) cin >> p[i];
    for (ll i = 0; i < n; i++) cin >> q[i];

    next_permutation(p.begin(), p.end());
    ll ans = 0;
    while (p < q) {
        next_permutation(p.begin(), p.end());
        ans++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}