#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, p, q;
    cin >> n >> p >> q;
    string s;
    cin >> s;

    ll ps, qs, k;
    for (ll i = 0; i <= n / p; i++) {
        if ((n - i * p) % q == 0) {
            ps = i, qs = (n - i * p) / q, k = ps + qs;
            cout << k << "\n";
            for (ll j = 0; j < ps; j++) {
                cout << s.substr(j * p, p) << "\n";
            }
            for (ll j = 0; j < qs; j++) {
                cout << s.substr(ps * p + j * q, q) << "\n";
            }
            return;
        }
    }
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}