#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll recurring_cycle(ll n) {
    map<pll, ll> divmod;
    ll ans = 0;
    ll div = 10;  // starting dividend
    for (ll i = 0; i < n + n / 10; i++) {
        if (div / n == 0) {
            div *= 10;
            divmod[{0, div% n}] = i;
            continue;
        }
        ll q = div / n, r = div % n;
        div = r * 10;
        if (r == 0) return 0;
        if (divmod.count({q, r})) return i - divmod[{q, r}];
        divmod[{q, r}] = i;
    }

    return ans;
}

void solve() {
    ll ans = 0, max_len = 0;
    for (ll d = 1; d < 1000; d++) {
        ll len = recurring_cycle(d);
        if (len >= max_len) {
            ans = d;
            max_len = len;
        }
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