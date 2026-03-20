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
    vector<ll> cnt(5);
    for (ll i = 0; i < n; i++) {
        ll si;
        cin >> si;
        cnt[si]++;
    }
    ll ans = cnt[4] + min(cnt[3], cnt[1]);
    ll diff = min(cnt[3], cnt[1]);
    cnt[3] -= diff;
    cnt[1] -= diff;
    ans += cnt[2] / 2;
    cnt[2] = cnt[2] % 2;
    ans += cnt[3];
    if (cnt[2] > 0) {
        ans += cnt[2];
        cnt[1] -= 2;
    }
    if (cnt[1] > 0) ans += (cnt[1] + 3) / 4;

    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}