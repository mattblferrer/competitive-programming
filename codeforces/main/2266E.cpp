#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<ll> get_pf(ll n) {
    vector<ll> ans;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) ans.push_back(n);
    return ans;
}

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll ans = 0;
    vector<ll> cnt(n + 1);
    for (ll i = 0; i < n; i++) {
        cnt[a[i]]++;
    }
    vector<ll> dp(n + 1), best_p(n + 1);
    for (ll i = k + 1; i <= n; i++) dp[i] = INF;
    for (ll i = k + 1; i <= n; i++) {
        vector<ll> pf = get_pf(i);
        for (ll p : pf) {
            if (1 + p * dp[i / p] < dp[i]) {
                dp[i] = 1 + p * dp[i / p];
                best_p[i] = p;
            }
        }
    }

    for (ll i = n; i >= k + 1; i--) {
        ans += cnt[i] * dp[i];
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