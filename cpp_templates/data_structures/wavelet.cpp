// Contents
//   WaveletMatrix   wavelet matrix: static order statistics on subarrays, online; values can be any integers
//   MergeSortTree   merge sort tree: static counting of values in a range, online

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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
            } else {
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
            } else {
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

// merge sort tree: static counting of values in a range, online
//   MergeSortTree(a)          build from a, O(n log n)
//   count_less(l, r, x)       number of i in [l, r) with a[i] < x, O(log^2 n)
//   count_range(l, r, x, y)   number of i in [l, r) with x <= a[i] < y, O(log^2 n)
struct MergeSortTree {
    int n;
    vector<vector<ll>> t;

    MergeSortTree(const vector<ll> &a): n(a.size()), t(2 * a.size()) {
        for (int i = 0; i < n; i++) t[n + i] = {a[i]};
        for (int i = n - 1; i > 0; i--) {
            t[i].resize(t[2 * i].size() + t[2 * i + 1].size());
            merge(t[2 * i].begin(), t[2 * i].end(), t[2 * i + 1].begin(), t[2 * i + 1].end(), t[i].begin());
        }
    }

    int count_less(int l, int r, ll x) const {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res += lower_bound(t[l].begin(), t[l].end(), x) - t[l].begin();
                l++;
            }
            if (r & 1) {
                r--;
                res += lower_bound(t[r].begin(), t[r].end(), x) - t[r].begin();
            }
        }
        return res;
    }

    int count_range(int l, int r, ll x, ll y) const { return count_less(l, r, y) - count_less(l, r, x); }
};
