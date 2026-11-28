#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, d;
    cin >> n >> d;
    ll ans = 0;
    vector<ll> a(1'000'001);
    for (ll i = 1; i <= n; i++) {
        ll si, ti;
        cin >> si >> ti;
        if (ti - si >= d) {
            a[si]++;
            a[ti - d + 1]--;
        }
    }
    ll curr = 0;
    for (ll i = 1; i <= 1'000'001; i++) {
        curr += a[i];
        ans += (curr * (curr - 1)) / 2;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}