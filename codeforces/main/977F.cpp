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
    vector<ll> dp(n), prev(n);
    map<ll, ll> idx;
    ll ans = -1, ans_i = -1;
    for (ll i = 0; i < n; i++) {
        if (idx.count(a[i] - 1) == 0) {
            dp[i] = 1;
            prev[i] = 0;
        }
        else {
            dp[i] = dp[idx[a[i] - 1]] + 1;
            prev[i] = idx[a[i] - 1];
        }
        idx[a[i]] = i;
        if (dp[i] > ans) {
            ans = dp[i];
            ans_i = i;
        }
    }
    vector<ll> seq(ans);
    for (ll i = 0; i < ans; i++) {
        seq[i] = ans_i + 1;
        ans_i = prev[ans_i];
    }
    reverse(seq.begin(), seq.end());
    cout << ans << "\n";
    for (int i = 0; i < ans; i++) cout << seq[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}