// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

void solve() {
    ll n;
    cin >> n;
    string s;
    cin >> s;

    ll ans = 0;
    vector<vector<ll>> pref(3, vector<ll>(n)), suff(3, vector<ll>(n));
    for (ll i = 0; i < 3; i++) {
        pref[i][0] = (s[0] == ('A' + i));
        suff[i][n - 1] = (s[n - 1] == ('A' + i));
        for (ll j = 1; j < n; j++) {
            pref[i][j] = pref[i][j - 1] + (s[j] == ('A' + i));
        }
        for (ll j = n - 2; j >= 0; j--) {
            suff[i][j] = suff[i][j + 1] + (s[j] == ('A' + i));
        }
    }
    vector<vector<ll>> occ(3);
    for (ll i = 0; i < n; i++) {
        occ[s[i] - 'A'].push_back(i);
    }
    for (ll i = 0; i < 3; i++) occ[i].push_back(9999999);

    ll left = 0, right = n;
    bool valid_left = false, valid_right = false, valid_mid = true;
    while (!valid_left) {
        if (right < left) {
            cout << "0\n";
            return;
        }

        valid_left = true;
        for (ll j = 0; j < 3; j++) {
            if (pref[j][left] == 0) valid_left = false;
        }
        left++;
    }
    while (!valid_right) {
        right--;
        if (right < left) {
            cout << "0\n";
            return;
        }

        valid_right = true;
        for (ll j = 0; j < 3; j++) {
            if (suff[j][right] == 0) valid_right = false;
        }
    }

    for (ll i = left; i < right; i++) {
        ll max_part = -INF;
        for (ll j = 0; j < 3; j++) {
            max_part = max(max_part, *upper_bound(occ[j].begin(), occ[j].end(), i - 1));
        }
        ans += max(0LL, right - max_part);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
