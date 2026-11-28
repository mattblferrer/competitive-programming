#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, w;
    cin >> n >> w;
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        a[i] = ai;
        b[i] = bi;
    }
    ll ans = 0;
    for (ll i = 0; i < (1 << n); i++) {
        ll curr = 0, currw = 0;
        for (ll j = 0; j < n; j++) {
            if (i & (1 << j)) {
                curr += a[j];
                currw += b[j];
                if (currw > w) break;
            }
        }
        if (currw <= w) ans = max(ans, curr);
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