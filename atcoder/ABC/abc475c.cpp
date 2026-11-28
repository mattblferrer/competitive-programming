#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, s, l;
    cin >> n >> s >> l;
    vector<ll> a(n);
    for (ll i = 1; i <= n - 1; i++) cin >> a[i];

    ll ans = 0;
    vector<ll> pref(n);
    for (ll i = 1; i <= n - 1; i++) pref[i] = a[i] + pref[i - 1];
    for (ll i = 1; i <= n; i++) {
        ll curr = 0, dist = 0;
        dist += abs(pref[s - 1] - pref[i - 1]);

        if (dist <= l) {
            curr = abs(s - i) + 1;
            ans = max(ans, curr);
            dist *= 2;
        }
        else continue;

        if (i <= s) {
            for (ll j = s; j <= n - 1; j++) {
                curr++;
                dist += a[j];
                if (dist > l) break;
                ans = max(ans, curr);
            }
        }
        else {
            for (ll j = s - 1; j >= 1; j--) {
                curr++;
                dist += a[j];
                if (dist > l) break;
                ans = max(ans, curr);
            }
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