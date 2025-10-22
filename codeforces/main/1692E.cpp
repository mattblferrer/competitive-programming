#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, s;
    cin >> n >> s;
    vector<ll> a(n + 1);
    ll ones = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i]) ones++;
    }
    a[n] = 1;
    if (ones < s) {
        cout << "-1\n";
        return;
    }
    ll l = -1, ans = n;
    ones = 0;
    for (ll r = 0; r <= n; r++) {
        if (a[r]) ones++;
        if (ones < s) continue;
        while (ones > s) {
            l++;
            if (a[l]) ones--;
        }
        ans = min(ans, n - (r - l));
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