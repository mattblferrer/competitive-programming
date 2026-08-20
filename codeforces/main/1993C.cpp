#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n), rem(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        rem[i] = a[i] % (2 * k);
    }

    if (n == 1) { cout << a.front() << "\n";return; }

    sort(a.begin(), a.end());
    sort(rem.begin(), rem.end());
    bool p1 = false, p2 = true;
    for (ll i = 0; i < n; i++) {
        ll seq = rem[(i + 1) % n] - rem[i];
        if (seq < 0) seq += 2 * k;
        if (seq > k) {
            p1 = true;
            break;
        }
        if (seq != 0) {
            p2 = false;
        }
    }
    if ((!p1) && (!p2)) {
        cout << "-1\n";
        return;
    }

    for (ll i = 0; i < n; i++) {
        ll need = (a.back() - a[i] + k - 1) / (2 * k);
        a[i] += (2 * k * need);
    }
    sort(a.begin(), a.end());
    ll ans = a.back();
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}