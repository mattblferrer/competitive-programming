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
    ll ft_sum = 0, a_sum = 0;
    for (ll i = 0; i < n; i++) {
        ll ft, a;
        cin >> ft >> a;
        ft_sum += ft;
        a_sum += a;
    }
    ld ans = (ld)ft_sum * (ld)100.0 / (ld)a_sum;
    cout << fixed << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(2);

    solve();
    return 0;
}