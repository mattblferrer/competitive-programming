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
    char c;
    string s;
    cin >> n >> c >> s;
    s += s;
    set<ll> gpos;
    for (ll i = 0; i < 2*n; i++) {
        if (s[i] == 'g') gpos.insert(i);
    }
    ll ans = 0, curr = 0;
    for (ll i = 0; i < 2*n; i++) {
        if (s[i] == c) {
            ans = max(ans, *gpos.lower_bound(i) - i);
        }
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