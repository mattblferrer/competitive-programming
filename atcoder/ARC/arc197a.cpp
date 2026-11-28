#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll h, w;
    cin >> h >> w;
    string s;
    cin >> s;
    ll d = 0, r = 0, q = 0;
    for (ll i = 0; i < s.size(); i++) {
        if (s[i] == 'D') d++;
        else if (s[i] == 'R') r++;
        else q++;
    }
    vector<ll> minh(w, h), maxh(w);

    // calculate min height area
    ll da = d, ra = r, x = 0, y = 0;
    for (ll i = 0; i < s.size(); i++) {
        minh[x] = min(minh[x], h - y - 1);
        if (s[i] == 'R') x++;
        else if (s[i] == '?') {
            if (da < h - 1) {
                y++;
                da++;
            }
            else {
                x++;
                ra++;
            }
        }
        else y++;
        minh[x] = min(minh[x], h - y - 1);
    }
    // calculate max height area
    da = d, ra = r, x = 0, y = 0;
    for (ll i = 0; i < s.size(); i++) {
        maxh[x] = max(maxh[x], h - y);
        if (s[i] == 'D') y++;
        else if (s[i] == '?') {
            if (ra < w - 1) {
                x++;
                ra++;
            }
            else {
                y++;
                da++;
            }
        }
        else x++;
        maxh[x] = max(maxh[x], h - y);
    }
    ll ans = 0;
    for (ll i = 0; i < w; i++) {
        ans += maxh[i] - minh[i];
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}