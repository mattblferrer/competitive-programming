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
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll curr = 1;
        for (ll j = i - 1; j >= 0; j--) {
            if (a[j] <= a[j + 1]) curr++;
            else break;
        }
        for (ll j = i + 1; j < n; j++) {
            if (a[j] <= a[j - 1]) curr++;
            else break;
        }
        ans = max(ans, curr);
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