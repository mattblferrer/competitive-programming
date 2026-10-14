#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    map<ll, vector<ll>> rem;
    ll sum = 0;
    rem[0].push_back(-1);

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        sum = (sum + a[i]) % k;
        rem[sum].push_back(i);
        ans += distance(rem[sum].begin(), lower_bound(rem[sum].begin(), rem[sum].end(), i - k));
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