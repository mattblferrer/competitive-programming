#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;


struct point_segtree {
    int n;
    ll *vals;
    point_segtree(vector<ll> &ar, int n) {
        this->n = n;
        vals = new ll[2 * n];
        for (int i = 0; i < n; ++i) vals[i + n] = ar[i];
        for (int i = n - 1; i > 0; --i) vals[i] = vals[i << 1] + vals[i << 1 | 1];
    }
    void update(int i, ll v) {
        for (vals[i += n] += v; i > 1; i >>= 1)
            vals[i >> 1] = vals[i] + vals[i ^ 1];
    }
    ll query(int l, int r) {
        ll res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += vals[l++];
            if (r & 1) res += vals[--r];
        }
        return res;
    }
};

struct range_segtree {
    ll i, j, val, temp_val = 0;
    range_segtree *l, *r;
    range_segtree(vector<ll> &ar, int _i, int _j): i(_i), j(_j) {
        if (i == j) {
            val = ar[i];
            l = r = NULL;
        }
        else {
            int k = (i + j) >> 1;
            l = new range_segtree(ar, i, k);
            r = new range_segtree(ar, k + 1, j);
            val = l->val + r->val;
        }
    }
    void visit() {
        if (temp_val) {
            val += (j - i + 1) * temp_val;
            if (l) {
                l->temp_val += temp_val;
                r->temp_val += temp_val;
            }
            temp_val = 0;
        }
    }
    void increase(int _i, int _j, ll _inc) {
        visit();
        if (_i <= i && j <= _j) {
            temp_val += _inc;
            visit();
        }
        else if (_j < i or j < _i) {
            // do nothing
        }
        else {
            l->increase(_i, _j, _inc);
            r->increase(_i, _j, _inc);
            val = l->val + r->val;
        }
    }
    ll query(int _i, int _j) {
        visit();
        if (_i <= i and j <= _j) return val;
        else if (_j < i || j < _i) return 0;
        else return l->query(_i, _j) + r->query(_i, _j);
    }
};
