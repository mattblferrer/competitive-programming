#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(n - 1);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n - 1; i++) cin >> b[i];

    ll ans = INF;
    for (ll start = 0; start < 2; start++) {
        ll curr = 0;
        vector<ll> a_cpy = a;
        if (start != a_cpy[0]) {
            a_cpy[0] = start;
            curr++;
        }
        for (ll i = 1; i < n; i++) {
            if ((a_cpy[i - 1] + a_cpy[i]) % 2 != b[i - 1]) {
                a_cpy[i] = 1 - a_cpy[i];
                curr++;
            }
        }
        ans = min(ans, curr);
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