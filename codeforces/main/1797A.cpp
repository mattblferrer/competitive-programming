#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<ll> moves_x = {0, 1, 0, -1};
vector<ll> moves_y = {1, 0, -1, 0};

void solve() {
    ll n, m;
    cin >> n >> m;
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ll cnt1 = 0;
    for (ll i = 0; i < 4; i++) {
        ll xt = x1 + moves_x[i], yt = y1 + moves_y[i];
        if ((xt <= 0) || (xt > n)) continue;
        if ((yt <= 0) || (yt > m)) continue;
        cnt1++;
    }
    ll cnt2 = 0;
    for (ll i = 0; i < 4; i++) {
        ll xt = x2 + moves_x[i], yt = y2 + moves_y[i];
        if ((xt <= 0) || (xt > n)) continue;
        if ((yt <= 0) || (yt > m)) continue;
        cnt2++;
    }
    cout << min(cnt1, cnt2) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}