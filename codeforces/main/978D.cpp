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
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) cin >> b[i];
    ll ans = INF;
    for (ll i = -1; i <= 1; i++) {
        for (ll j = -1; j <= 1; j++) {
            ll start = b[0] + i, end = b[n - 1] + j;
            ll rem, jump;
            if (end == start || n == 1) {
                rem = 0;
                jump = 0;
            }
            else {
                rem = (end - start) % (n - 1);
                jump = (end - start) / (n - 1);
            }
            if (rem != 0) continue;
            bool valid = true;
            ll curr = 0;
            for (ll k = 0; k < n; k++) {
                if (abs(b[k] - (start + jump * k)) > 1) {
                    valid = false;
                    break;
                }
                else curr += abs(b[k] - (start + jump * k));
            }
            if (valid) ans = min(ans, curr);
        }
    }
    if (ans == INF) cout << "-1\n";
    else cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}