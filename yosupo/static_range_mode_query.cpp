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

// static range mode, online: {a mode of a[l, r), its count}; values can be any integers
// blocks of about sqrt n elements with the mode of every run of whole blocks precomputed; a query starts from that and
// tries each leftover element by jumping in its value's position list (a value whose first occurrence in [l, r) is a
// left leftover is counted from there forward, one whose last occurrence is a right leftover backward)
//   RangeMode(a)   build, O(n sqrt n) time, O(n) memory
//   query(l, r)    {mode, count} of a[l, r), l < r, O(sqrt n)
struct RangeMode {
    int n, bs;
    vector<ll> vals;
    vector<int> c, at;                    // compressed value of a[i], index of i in pos[c[i]]
    vector<vector<int>> pos;              // positions of each value, increasing
    vector<vector<pair<int, int>>> blk;  // blk[i][j] = {mode, count} of blocks i..j

    RangeMode(const vector<ll> &a): n(a.size()), vals(a), c(n), at(n) {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        pos.resize(vals.size());
        for (int i = 0; i < n; i++) {
            c[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
            at[i] = pos[c[i]].size();
            pos[c[i]].push_back(i);
        }
        bs = max(1, (int)sqrt(n));
        int nb = (n + bs - 1) / bs;
        blk.assign(nb, vector<pair<int, int>>(nb));
        vector<int> cnt(vals.size());
        for (int i = 0; i < nb; i++) {
            pair<int, int> best{0, 0};
            for (int j = i; j < nb; j++) {
                for (int p = j * bs; p < min(n, (j + 1) * bs); p++) {
                    if (++cnt[c[p]] > best.second) best = {c[p], cnt[c[p]]};
                }
                blk[i][j] = best;
            }
            for (int p = i * bs; p < n; p++) cnt[c[p]]--;
        }
    }

    pair<ll, int> query(int l, int r) const {
        int bl = (l + bs - 1) / bs, br = r / bs, lend = r, rbeg = r;  // whole blocks bl..br-1
        int mode = c[l], best = 0;
        if (bl < br) tie(mode, best) = blk[bl][br - 1], lend = bl * bs, rbeg = br * bs;
        for (int p = l; p < lend; p++) {
            const vector<int> &ps = pos[c[p]];
            while (at[p] + best < (int)ps.size() && ps[at[p] + best] < r) best++, mode = c[p];
        }
        for (int p = rbeg; p < r; p++) {
            const vector<int> &ps = pos[c[p]];
            while (at[p] - best >= 0 && ps[at[p] - best] >= l) best++, mode = c[p];
        }
        return {vals[mode], best};
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    RangeMode rm(a);
    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        auto [mode, cnt] = rm.query(l, r);
        cout << mode << " " << cnt << "\n";
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
