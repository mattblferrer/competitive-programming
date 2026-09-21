#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> b(n);
    for (ll i = 0; i < n; i++) b[i] = a[i] - i;
    set<ll> b_set(b.begin(), b.end());
    vector<ll> bu(b_set.begin(), b_set.end());

    ll ans = 1, curr = 1;
    for (ll i = 1; i < bu.size(); i++) {
        if (bu[i - 1] == bu[i] - 1) curr++;
        else curr = 1;
        ans = max(ans, curr);
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