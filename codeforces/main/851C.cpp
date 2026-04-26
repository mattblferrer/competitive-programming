#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ld scalar_product(vector<ll> x, vector<ll> y) {
    ld ans = 0;
    for (ll i = 0; i < 5; i++) ans += x[i]*y[i];
    return ans;
}

ld length(vector<ll> x) {
    ld ans = 0;
    for (ll i = 0; i < 5; i++) ans += x[i]*x[i];
    return sqrtl(ans);
}

ld angle(vector<ll> x, vector<ll> y) {
    return acos(scalar_product(x, y) / (length(x) * length(y))) * 180.0 / M_PI;
}

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> pts(n, vector<ll>(5));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < 5; j++) cin >> pts[i][j];        
    }
    if (n > 32) {
        cout << 0 << "\n";
        return;
    }
    vector<ll> good_pts;
    for (ll i = 0; i < n; i++) {
        bool good = true;
        for (ll j = 0; j < n; j++) {
            for (ll k = 0; k < n; k++) {
                if ((i == j) || (i == k) || (j == k)) continue;
                vector<ll> ab(5), ac(5);
                for (ll ctr = 0; ctr < 5; ctr++) {
                    ab[ctr] = pts[j][ctr] - pts[i][ctr];
                    ac[ctr] = pts[k][ctr] - pts[i][ctr]; 
                }
                ld a = angle(ab, ac);
                if (a < 90.0) good = false;
                // cout << i << " " << j << " " << k << " " << a << "\n";
            }
        }
        if (good) good_pts.push_back(i + 1);
    }
    cout << good_pts.size() << "\n";
    for (ll i = 0; i < good_pts.size(); i++) {
        cout << good_pts[i] << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}