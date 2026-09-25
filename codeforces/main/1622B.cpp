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
    vector<ll> p(n), q(n);
    for (ll i = 0; i < n; i++) cin >> p[i];
    string s;
    cin >> s;

    vector<ll> zeros, ones;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') zeros.push_back(p[i]);
        else ones.push_back(p[i]);
    }
    sort(zeros.begin(), zeros.end());
    sort(ones.begin(), ones.end());
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') q[i] = 1 + distance(zeros.begin(), lower_bound(zeros.begin(), zeros.end(), p[i]));
        else q[i] = zeros.size() + 1 + distance(ones.begin(), lower_bound(ones.begin(), ones.end(), p[i]));
    }

    for (ll i = 0; i < n; i++) cout << q[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}