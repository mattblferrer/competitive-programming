// Contents
//   MinOp           example idempotent op (min) for SparseTable
//   SparseTable     static range query for idempotent ops (min, max, gcd), O(1)
//   SparseTable2D   static rectangle query for idempotent ops

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// sparse table; S must be idempotent, e.g. min, max, gcd, and shaped like MinOp
struct MinOp {
    using T = ll;
    static T op(const T &a, const T &b) { return min(a, b); }
};

// SparseTable<S>: static range query
//   SparseTable(a)   build from a, O(n log n)
//   query(l, r)      op over [l, r); requires l < r, O(1)
template <class S>
struct SparseTable {
    using T = typename S::T;
    vector<vector<T>> t;

    SparseTable(const vector<T> &a = {}): t(1, a) {
        int n = a.size();
        for (int j = 1; (1 << j) <= n; j++) {
            t.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++)
                t[j][i] = S::op(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
        }
    }

    T query(int l, int r) const {
        int k = __lg(r - l);
        return S::op(t[k][l], t[k][r - (1 << k)]);
    }
};

// SparseTable2D<S>: static rectangle query, S as above
//   SparseTable2D(a)            build from grid a, O(nm log n log m)
//   query(r1, c1, r2, c2)       op over [r1, r2) x [c1, c2); requires r1 < r2 and c1 < c2, O(1)
template <class S>
struct SparseTable2D {
    using T = typename S::T;
    vector<vector<vector<vector<T>>>> t;  // t[a][b][i][j] covers [i, i + 2^a) x [j, j + 2^b)

    SparseTable2D(const vector<vector<T>> &g) {
        int n = g.size(), m = g[0].size(), la = __lg(n) + 1, lb = __lg(m) + 1;
        t.assign(la, vector<vector<vector<T>>>(lb, vector<vector<T>>(n, vector<T>(m))));
        for (int a = 0; a < la; a++) {
            for (int b = 0; b < lb; b++) {
                for (int i = 0; i + (1 << a) <= n; i++) {
                    for (int j = 0; j + (1 << b) <= m; j++) {
                        if (a == 0 && b == 0) t[a][b][i][j] = g[i][j];
                        else if (b > 0) t[a][b][i][j] = S::op(t[a][b - 1][i][j], t[a][b - 1][i][j + (1 << (b - 1))]);
                        else t[a][b][i][j] = S::op(t[a - 1][b][i][j], t[a - 1][b][i + (1 << (a - 1))][j]);
                    }
                }
            }
        }
    }

    T query(int r1, int c1, int r2, int c2) const {
        int a = __lg(r2 - r1), b = __lg(c2 - c1);
        return S::op(S::op(t[a][b][r1][c1], t[a][b][r1][c2 - (1 << b)]),
                     S::op(t[a][b][r2 - (1 << a)][c1], t[a][b][r2 - (1 << a)][c2 - (1 << b)]));
    }
};
