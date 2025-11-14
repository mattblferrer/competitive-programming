#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll ans = INF, curr = 0, len = 0, left = 0;
    for (ll i = 0; i < n; i++) {
        curr += a[i];
        len++;
        while (curr >= x) {
            ans = min(ans, len);
            len--;
            curr -= a[left];
            left++;
        }
    }
    if (ans == INF) cout << -1;
    else cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}