// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// Manacher's algorithm, O(n); returns {d1, d2}
// d1[i] = number of odd palindromes centered at i, so the longest is s[i - d1[i] + 1 .. i + d1[i] - 1]
// d2[i] = number of even palindromes whose right center is i, so the longest is s[i - d2[i] .. i + d2[i] - 1]
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k;
        if (i + k - 1 > r) l = i - k + 1, r = i + k - 1;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
    return {d1, d2};
}

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    auto [d1, d2] = manacher(s);
    for (ll i = 0; i < 2 * n - 1; i++) {
        if (i % 2 == 0) cout << 2 * d1[i / 2] - 1 << " ";  // centered on s[i / 2]
        else cout << 2 * d2[(i + 1) / 2] << " ";  // centered between s[i / 2] and s[i / 2 + 1]
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
