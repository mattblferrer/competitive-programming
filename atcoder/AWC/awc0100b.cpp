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
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<ll> score(n);
    for (ll i = 0; i < n; i++) score[i] = a[i] + b[i];
    ll max_score = 0, ans = 0;
    for (ll i = 0; i < n; i++) {
        if (score[i] > max_score) {
            max_score = score[i];
            ans = i + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}