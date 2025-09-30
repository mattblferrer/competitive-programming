#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

struct vec {
    ld x, y;
    ll idx;
};

void solve() {
    ll n;
    ld x, y;
    cin >> n;
    vector<vec> vecs(n);
    for (ll i = 0; i < n; i++) {
        cin >> x >> y;
        vecs[i].x = x;
        vecs[i].y = y;
        vecs[i].idx = i;
    }
    sort(vecs.begin(), vecs.end(), [](vec a, vec b) {
        return atan2(a.y, a.x) < atan2(b.y, b.x);
    });
    ld min_diff = INF;
    ll idx_1 = 0, idx_2 = 0;
    for (ll i = 0; i < n; i++) {
        ld diff = atan2(vecs[(i + 1) % n].y, vecs[(i + 1) % n].x) - atan2(vecs[i].y, vecs[i].x);
        if (diff < 0) diff += 2 * M_PI;
        if (diff < min_diff) {
            min_diff = diff;
            idx_1 = vecs[i].idx + 1;
            idx_2 = vecs[(i + 1) % n].idx + 1;
        }
    }
    cout << idx_1 << " " << idx_2;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}