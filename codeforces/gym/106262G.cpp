#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, b;
    cin >> n >> b;
    vector<ll> x(n - 1);
    for (ll i = 0; i < n - 1; i++) cin >> x[i];
    ll ans = b, cnt = 0;
    for (ll i = 0; i < n - 1; i++) {
        if (x[i] >= 0) {
            ans += x[i];
            cnt++;
        }
    }
    if (cnt == 0) {
        ans += *max_element(x.begin(), x.end());
        if (ans < 0) cout << -1;
        else cout << ans;
        return;
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}