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
    vector<ll> m(n), r(n);
    for (ll i = 0; i < n; i++) cin >> m[i];
    for (ll i = 0; i < n; i++) cin >> r[i];
    ll valid = 0, total = 1;
    for (ll i = 0; i < n; i++) {
        total = lcm(total, m[i]);
    }
    for (ll i = 0; i < total; i++) {
        bool curr = true;
        for (ll j = 0; j < n; j++) {
            if (i % m[j] == r[j]) {
                valid++;
                break;
            }
        }
    }
    cout << (ld)(valid) / total;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}