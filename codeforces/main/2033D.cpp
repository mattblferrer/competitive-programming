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
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    vector<ll> pref(n + 1);
    for (ll i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];

    map<ll, ll> last_seen;
    last_seen[0] = 1;
    ll ans = 0;
    ll last = 0;
    for (ll i = 1; i <= n; i++) {
        if (last_seen.count(pref[i]) == 0) {
            last_seen[pref[i]] = i;
            continue;
        }
        if (last_seen[pref[i]] >= last) {
            for (ll j = last_seen[pref[i]]; j <= i; j++) {
                last_seen[pref[j]] = 0;
            }
            last = i;
            ans++;
        }
        last_seen[pref[i]] = i;
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