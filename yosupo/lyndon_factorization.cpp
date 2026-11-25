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

// Lyndon factorization (Duval): returns 0 = a[0] < a[1] < ... < a[k] = n so that the s[a[i], a[i + 1]) are Lyndon
// words (strictly smaller than all their proper rotations) in nonincreasing order, O(n)
template <class S>
vector<int> lyndon_factorization(const S &s) {
    int n = s.size();
    vector<int> res{0};
    for (int i = 0; i < n;) {
        int j = i + 1, k = i;  // s[i, j) is a prefix of repeated copies of a Lyndon word of length j - k
        while (j < n && s[k] <= s[j]) {
            k = s[k] < s[j] ? i : k + 1;
            j++;
        }
        for (; i <= k; i += j - k) res.push_back(i + j - k);
    }
    return res;
}

void solve() {
    string s;
    cin >> s;
    for (int x : lyndon_factorization(s)) cout << x << " ";
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
