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
    vector<ll> x(n + 1);
    for (ll i = 1; i <= n; i++) cin >> x[i];
    set<ll> x_set(x.begin() + 1, x.end());

    if (x_set.size() < n) {  // has missing number
        for (ll i = 1; i <= n; i++) {
            if (x_set.count(i) == 0) {
                if (i == n) cout << "? " << i << " " << n - 1 << endl;
                else cout << "? " << i << " " << n << endl;

                ll a1;
                cin >> a1;
                if (a1 == 0) cout << "! A" << endl;
                else cout << "! B" << endl;
                return;
            }
        }
    }
    else {
        ll max_x = 0, min_x = INF, max_i, min_i;
        for (ll i = 1; i <= n; i++) {
            if (max_x < x[i]) {
                max_x = x[i];
                max_i = i;
            }
            if (min_x > x[i]) {
                min_x = x[i];
                min_i = i;
            }
        }

        cout << "? " << min_i << " " << max_i << endl;
        ll a1;
        cin >> a1;
        cout << "? " << max_i << " " << min_i << endl;
        ll a2;
        cin >> a2;
        if ((a1 == 0) || (a2 == 0)) cout << "! A" << endl;
        else if ((a1 >= n - 1) && (a2 >= n - 1)) cout << "! B" << endl;
        else cout << "! A" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}