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

// wavelet matrix: static order statistics on subarrays, online; values can be any integers
// B = number of bits needed for the distinct values, about log n
//   WaveletMatrix(a)      build from a, O(n log n)
//   kth(l, r, k)          k-th smallest value (0-indexed) in a[l..r); requires k < r - l, O(B)
//   count_less(l, r, x)   number of i in [l, r) with a[i] < x, O(B + log n)
//   count_eq(l, r, x)     number of i in [l, r) with a[i] == x, O(B + log n)
struct WaveletMatrix {
    int bits = 1;
    vector<ll> vals;
    vector<vector<int>> zeros;  // zeros[b][i] = number of the first i elements with this bit 0, at level b
    vector<int> mid;

    WaveletMatrix(const vector<ll> &a): vals(a) {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        while ((1LL << bits) < (ll)vals.size()) bits++;
        int n = a.size();
        vector<int> cur(n), left, right;
        for (int i = 0; i < n; i++) cur[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        zeros.assign(bits, vector<int>(n + 1, 0));
        mid.assign(bits, 0);
        for (int b = 0; b < bits; b++) {
            int bit = bits - 1 - b;
            left.clear();
            right.clear();
            for (int i = 0; i < n; i++) {
                bool one = cur[i] >> bit & 1;
                zeros[b][i + 1] = zeros[b][i] + !one;
                (one ? right : left).push_back(cur[i]);
            }
            mid[b] = left.size();
            cur = left;
            cur.insert(cur.end(), right.begin(), right.end());
        }
    }

    ll kth(int l, int r, int k) const {
        int res = 0;
        for (int b = 0; b < bits; b++) {
            int zl = zeros[b][l], zr = zeros[b][r];
            if (k < zr - zl) {
                l = zl;
                r = zr;
            }
            else {
                k -= zr - zl;
                res |= 1 << (bits - 1 - b);
                l = mid[b] + l - zl;
                r = mid[b] + r - zr;
            }
        }
        return vals[res];
    }

    int count_id_less(int l, int r, int id) const {  // id is a position in vals
        if (id >= (int)vals.size()) return r - l;
        int res = 0;
        for (int b = 0; b < bits; b++) {
            int zl = zeros[b][l], zr = zeros[b][r];
            if (id >> (bits - 1 - b) & 1) {
                res += zr - zl;
                l = mid[b] + l - zl;
                r = mid[b] + r - zr;
            }
            else {
                l = zl;
                r = zr;
            }
        }
        return res;
    }

    int count_less(int l, int r, ll x) const {
        return count_id_less(l, r, lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    }

    int count_eq(int l, int r, ll x) const {
        int id = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        if (id == (int)vals.size() || vals[id] != x) return 0;
        return count_id_less(l, r, id + 1) - count_id_less(l, r, id);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    WaveletMatrix wm(a);

    for (ll i = 0; i < q; i++) {
        ll li, ri, ki;
        cin >> li >> ri >> ki;
        cout << wm.kth(li, ri, ki) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
