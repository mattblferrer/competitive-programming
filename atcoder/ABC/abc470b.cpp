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
    vector<ll> c(n);
    for (ll i = 0; i < n; i++) cin >> c[i];

    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) cnt[c[i]]++;
    ll max_val = 0;
    for (const auto &pair : cnt) {
        max_val = max(max_val, pair.second);
    }
    cout << n - max_val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}