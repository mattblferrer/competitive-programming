#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<ll> as(a.begin(), a.end());
    sort(as.begin(), as.end());

    ll pref = 0, suff = 0;
    for (ll i = 0; i < n; i++) {
        if (as[i] == a[i]) pref++;
        else break;
    }
    for (ll i = n - 1; i >= 0; i--) {
        if (as[i] == a[i]) suff++;
        else break;
    }
    if (n - pref - suff <= k) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}