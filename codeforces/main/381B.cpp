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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    map<ll, ll> cnt;
    ll max_ai = 0;
    for (ll i = 0; i < n; i++) {
        cnt[a[i]]++;
        max_ai = max(max_ai, a[i]);
    }
    ll ans = 0;
    vector<ll> up, down;
    for (const auto &[ai, c] : cnt) {
        up.push_back(ai);
        if ((c > 1) && (ai != max_ai)) down.push_back(ai);

    }
    cout << up.size() + down.size() << "\n";
    for (ll i = 0; i < up.size(); i++) cout << up[i] << " ";
    for (ll i = down.size() - 1; i >= 0; i--) cout << down[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}