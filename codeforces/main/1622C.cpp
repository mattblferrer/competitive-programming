#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

ll get_steps(vector<ll> &a, ll m, ll k) {
    ll n = a.size(), ans = max(0LL, a[0] - m);
    ll sum = m - a[0];
    for (ll i = 0; i < n; i++) sum += a[i];
    if (sum <= k) return ans;

    for (ll i = n - 1; i > 0; i--) {
        sum -= a[i] - m;
        ans++;
        if (sum <= k) return ans;
    }
    return INF;
}

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll sum = 0;
    for (ll i = 0; i < n; i++) sum += a[i];

    sort(a.begin(), a.end());
    ll left = -1e12 - 1, right = 1e12 + 1;
    while (right - left >= 500) {
        ll m1 = left + (right - left) / 3;
        ll m2 = right - (right - left) / 3;
        ll sm1 = get_steps(a, m1, k), sm2 = get_steps(a, m2, k);
        if (sm1 > sm2) left = m1;
        else right = m2;
    }
    ll ans = INF;
    for (ll i = left; i <= right; i++) {
        ans = min(ans, get_steps(a, i, k));
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}