#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, d;
    cin >> n >> d;
    d--;
    vector<ll> s(n), p(n);
    for (ll i = 0; i < n; i++) cin >> s[i];
    for (ll i = 0; i < n; i++) cin >> p[i];

    s[d] += p[0];
    ll new_pts = s[d];
    sort(s.begin(), s.end(), greater<ll>());

    ll c = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == new_pts) {
            c = i;
            break;
        }
    }
    for (ll i = 0; i < c; i++) {
        s[i] += p[i + 1];
    }
    for (ll i = c + 1; i < n; i++) {
        s[i] += p[n + (c + 1) - i - 1];
    }
    sort(s.begin(), s.end(), greater<ll>());
    for (ll i = 0; i < n; i++) {
        if (s[i] == new_pts) {
            cout << i + 1;
            return;
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