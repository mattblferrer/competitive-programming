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
    vector<ll> a(2 * n + 1);
    for (ll i = 1; i <= 2 * n; i++) cin >> a[i];

    vector<ll> startp(2 * n + 2), endp(2 * n + 2), altp(2 * n + 2);
    for (ll i = 1; i <= 2 * n; i++) {
        startp[i] = startp[i - 1] + a[i];
    }
    for (ll i = 2 * n; i >= 1; i--) {
        endp[i] = endp[i + 1] + a[i];
    }
    altp[1] = a[1];
    for (ll i = 2; i <= 2 * n; i++) {
        altp[i] = altp[i - 2] + a[i];
    }
    vector<ll> ans(2 * n + 1);
    for (ll i = 1; i <= n; i++) {
        ans[i] = endp[2 * n - i + 1] - startp[i];
        ans[i] += (altp[2 * n - i - 1] - altp[i - 1]) - (altp[2 * n - i] - altp[i]);
    }

    for (ll i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}