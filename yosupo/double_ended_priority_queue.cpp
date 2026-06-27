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
    multiset<ll> s;
    for (ll i = 0; i < n; i++) {
        ll si; cin >> si;
        s.insert(si);
    }
    for (ll i = 0; i < q; i++) {
        ll t; cin >> t;
        if (t == 0) {
            ll x; cin >> x;
            s.insert(x);
        }
        else if (t == 1) {
            ll k = *s.begin();
            cout << k << "\n";
            s.extract(k);
        }
        else if (t == 2) {
            ll k = *s.rbegin();
            cout << k << "\n";
            s.extract(k);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}