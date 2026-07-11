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

    ll total = 0;
    set<pll> corners;  // corners of current polygon
    ll minx = INF, maxx = -1, miny = INF, maxy = -1;
    for (ll i = 0; i < n; i++) {
        ll x, y, w, h;
        cin >> x >> y >> w >> h;
        total += w * h;
        if (total > INF) {
            cout << "no\n";
            return;
        }

        minx = min(minx, x);
        maxx = max(maxx, x + w);
        miny = min(miny, y);
        maxy = max(maxy, y + h);

        // corners of current rectangle
        vector<pll> r_corners = {{x, y}, {x + w, y}, {x, y + h}, {x + w, y + h}};
        for (pll c : r_corners) {
            if (corners.count(c)) corners.erase(c);
            else corners.insert(c);
        }
    }

    ll area = (maxx - minx) * (maxy - miny);
    if ((area != total) || (corners.size() != 4)) {
        cout << "no\n";
        return;
    }
    set<pll> f_corners = {{minx, miny}, {minx, maxy}, {maxx, miny}, {maxx, maxy}};
    for (pll c : corners) {
        if (f_corners.count(c) == 0) {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}