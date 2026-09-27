#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<pll> orders(n);
    for (ll i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        orders[i] = {l, r};
    }
    sort(orders.begin(), orders.end(), [](pll a, pll b) {
        return a.second < b.second;
        });
    ll ans = 0, last = -INF;
    for (ll i = 0; i < n; i++) {
        if (last < orders[i].first) {
            ans++;
            last = orders[i].second;
        }
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