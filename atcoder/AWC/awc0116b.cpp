#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];

    vector<pll> ing(n);
    for (ll i = 0; i < n; i++) ing[i] = {a[i], b[i]};
    sort(ing.begin(), ing.end(), [](pll a, pll b){
        return a.second - a.first > b.second - b.first;
    });
    ll ans = 0;
    for (ll i = 0; i < k; i++) ans += ing[i].second;
    for (ll i = k; i < n; i++) ans += ing[i].first;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}