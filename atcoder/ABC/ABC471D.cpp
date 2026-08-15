#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll q, v;
    cin >> q >> v;
    multiset<ll> batt;
    for (ll i = 1; i <= q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll tq, wq;
            cin >> tq >> wq;
            batt.insert(tq - wq);
        }
        else if (type == 2) {
            ll tq;
            cin >> tq;
            if (batt.size() == 0) {
                cout << "-1\n";
                continue;
            }
            ll first = *(batt.begin());
            cout << min(tq - first, v) << "\n";
            batt.extract(first);
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