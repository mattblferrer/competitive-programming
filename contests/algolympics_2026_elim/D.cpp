#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll n, m;
vector<ll> b;
vector<ll> prefix_sum;

ll winner(ll a, ll bval) {
    return (prefix_sum[bval] - prefix_sum[a] > 0) ? 1 : 0;
}

void solve() {
    cin >> n >> m;
    b.resize(m);
    for (ll i = 0; i < m; i++) cin >> b[i];
    string s;
    cin >> s;

    prefix_sum.assign(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + (s[i] == '1' ? 1 : -1);
    }
    ll full = 1 << m;
    vector<ll> total(full);
    for (ll taken = 1; taken < full; taken++) {
        ll i = __builtin_ctz(taken);         // index of lowest set bit
        total[taken] = total[taken & (taken - 1)] + b[i];
    }

    // dp[taken] = max barrios won using exactly the barrios in taken
    vector<ll> dp(full);
    for (ll taken = 0; taken < full - 1; taken++) {
        ll l = total[taken];
        for (ll i = 0; i < m; i++) {
            if (taken & (1 << i)) continue;
            ll r = l + b[i];
            ll new_taken = taken | (1 << i);
            dp[new_taken] = max(dp[new_taken], dp[taken] + winner(l, r));
        }
    }
    cout << dp[full - 1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    ll t; cin >> t; while (t--) solve();
    return 0;
}