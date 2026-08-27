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
    vector<ll> m(n);
    for (ll i = 0; i < n; i++) cin >> m[i];

    ll sum = 0;
    for (ll i = 0; i < n; i++) sum += m[i];
    sort(m.begin(), m.end());
    vector<ll> m_end(n, sum / n);
    for (ll i = n - 1; i >= n - sum % n; i--) m_end[i]++;

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ans += abs(m_end[i] - m[i]);
    }
    ans /= 2;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}