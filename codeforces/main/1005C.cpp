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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) cnt[a[i]]++;

    ll ans = 0;
    for (auto pair : cnt) {
        ll ai = pair.first;
        bool found = false;
        for (ll p = 1; p <= 2 * powl(10, 9); p *= 2) {
            ll aj = p - ai;
            if (aj <= 0) continue;
            if ((ai == aj) && (cnt[aj] > 1)) {
                found = true;
                break;
            }
            else if ((ai != aj) && (cnt.count(aj))) {
                found = true;
                break;
            }
        }
        if (!found) ans += pair.second;
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