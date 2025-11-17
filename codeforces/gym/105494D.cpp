#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n + 1);
    for (ll i = 0; i < n; i++) cin >> a[i];
    a[n] = INF;
    sort(a.begin(), a.end());
    ll ans = 0, curr = 1, first = a[0];
    for (ll i = 1; i <= n; i++) {
        curr++;
        if ((curr > k) || (a[i] - first > m)) {
            first = a[i];
            curr = 1;
            ans++;
        }
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