#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ld calc_loss(vector<ll> &a, ld x) {
    ld sum = 0;
    for (ll i = 1; i < a.size(); i++) {
        sum += x + a[i] - min((ld)a[i], 2 * x);
    }
    return sum / (a.size() - 1);
}

ld ternary_search(vector<ll> &a, ld l, ld r) {
    ld eps = 1e-6;
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = calc_loss(a, m1);
        double f2 = calc_loss(a, m2);
        if (f1 > f2)
            l = m1;
        else
            r = m2;
    }
    return calc_loss(a, l);
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];
    ld ans = ternary_search(a, 0, 1e9);

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}