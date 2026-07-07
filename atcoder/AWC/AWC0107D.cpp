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

    ll left = -1, right = 2 * powl(10, 18);
    while (right - left > 1) {
        vector<ll> test = a;
        ll curr = 0;
        ll mid = (left + right) / 2;
        for (ll i = 0; i < n; i++) {
            if (test[i] < mid) {
                curr += mid - test[i];
                test[i] = mid;
            }
            if (curr >= k) break;
        }
        if (curr >= k) right = mid;
        else left = mid;
    }
    ll ans = 1, sum = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] < left) {
            sum += left - a[i];
            a[i] = left;
        }
    }
    for (ll i = 0; i < k - sum; i++) a[i]++;
    for (ll i = 0; i < n; i++) ans = (ans * (a[i] % MOD)) % MOD;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}