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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll sum = 0;
    for (ll rep = 0; rep < 2; rep++) {
        ll mad = 0;
        set<ll> a_set;
        vector<ll> b(n);
        for (ll i = 0; i < n; i++) {
            sum += a[i];
            if (a_set.count(a[i])) mad = max(mad, a[i]);
            else a_set.insert(a[i]);
            b[i] = mad;
        }
        a = b;
    }
    for (ll i = 0; i < n; i++) {
        sum += (n - i) * 1LL * a[i];
    }

    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}