#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> above(n + 1, 0), below(n + 1, 0);
    for (ll i = 1; i <= q; i++) {
        ll ci, pi;
        cin >> ci >> pi;

        above[pi] = ci;
        above[below[ci]] = 0;
        below[ci] = pi;
    }

    vector<ll> ans(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        if (below[i] != 0) continue;
        ans[i]++;

        ll k = i;
        while (above[k] != 0) {
            k = above[k];
            ans[i]++;
        }
    }

    for (ll i = 1; i <= n; i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}