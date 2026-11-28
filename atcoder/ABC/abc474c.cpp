#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> p(n), a(q);
    for (ll i = 0; i < n; i++) cin >> p[i];
    for (ll i = 0; i < q; i++) cin >> a[i];

    vector<bool> seen(n + 1);
    deque<ll> ans;
    for (ll i = q - 1; i >= 0; i--) {
        if (!seen[a[i]]) {
            ans.push_front(a[i]);
            seen[a[i]] = true;
        }
    }

    for (ll i = n - 1; i >= 0; i--) {
        if (!seen[p[i]]) ans.push_front(p[i]);
    }
    for (ll i = 0; i < n; i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}