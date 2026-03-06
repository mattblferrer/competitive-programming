#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    ll sum = 0, odd = 0, even = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) even++;
        else odd++;
        sum += a[i];
    }
    for (ll i = 0; i < q; i++) {
        ll type, x;
        cin >> type >> x;
        if (type == 0) {
            sum += x*even;
            if (x % 2 != 0) {
                odd += even;
                even = 0;
            }
        }
        else {
            sum += x*odd;
            if (x % 2 != 0) {
                even += odd;
                odd = 0;
            }
        }
        cout << sum << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}