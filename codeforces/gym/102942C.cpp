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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    ll ans = 0;
    for (ll i = n - 1; i >= 0; i--) {
        if (a[i] >= k) {
            ans++;
            a.pop_back();
        }
        else break;
    }
    multiset<ll> a_set(a.begin(), a.end());
    for (ll i = 0; i < a.size(); i++) {
        if (a_set.count(a[i]) == 0) continue;
        a_set.extract(a[i]);
        auto it = a_set.lower_bound(k - a[i]);
        if (it == a_set.end()) continue;
        ll p = *it;
        if (a[i] + p >= k) {
            ans++;
            a_set.extract(p);
        }
    }
    cout << ans << '\n';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}