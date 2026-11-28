#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct Star {
    ld x, y;
};

void solve() {
    ll n;
    cin >> n;
    vector<Star> inp(n);
    for (ll i = 0; i < n; i++) {
        ld xi, yi;
        cin >> xi >> yi;
        inp[i] = {xi, yi};
    }
    sort(inp.begin(), inp.end(), [](const Star &a, const Star &b) {
        bool up_a = a.y > 0 || ((a.y == 0) && (a.x >= 0));
        bool up_b = b.y > 0 || ((b.y == 0) && (b.x >= 0));
        if (up_a != up_b) return up_a;

        ll cross = a.x * b.y - a.y * b.x;
        if (cross != 0) return cross > 0;

        ll dist_a = a.x * a.x + a.y * a.y;
        ll dist_b = b.x * b.x + b.y * b.y;
        return dist_a < dist_b;
        });

    vector<Star> stars(2 * n);
    for (ll i = 0; i < n; i++) {
        stars[i] = inp[i];
        stars[i + n] = inp[i];
    }

    ll ans = 0;
    ll left = 0, right = 0;
    while (left < n) {
        while ((left + n > right) &&
            ((stars[left].x * stars[right].y - stars[left].y * stars[right].x) >= 0)) {
            right++;
        }
        ans = max({ans, right - left});
        left++;
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