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
    map<ll, pll> pts;
    for (ll i = 0; i < n; i++) {
        ll li, ri;
        cin >> li >> ri;
        pts[li].first++;
        pts[ri].second--;
    }
    vector<pll> ans;
    ll left = -INF, curr = 0;
    bool segment = false;
    for (auto &[pt, pair] : pts) {
        ll inc = pair.first, dec = pair.second;
        curr += inc;
        if ((curr >= k) && !segment) {
            segment = true;
            left = pt;
        }
        curr += dec;
        if ((curr < k) && segment) {
            segment = false;
            ans.push_back({left, pt});
        }
    }
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}