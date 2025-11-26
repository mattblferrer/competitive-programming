#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    set<ll> factors;
    const ll c = min(a, b), d = max(a, b);
    for (ll i = 1; i*i <= c; i++) {
        if (c % i == 0) {
            if (d % i == 0) factors.insert(i);
            if (d % (c / i) == 0) factors.insert(c / i);
        }
    }
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll low, high, ans = -1;
        cin >> low >> high;
        for (ll f: factors) {
            if ((low <= f) && (f <= high)) ans = max(ans, f);
        }
        cout << ans << "\n";
    }   
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}