// Contents
//   SumM            basic monoids: SumM, MinM, MaxM, GcdM, XorM
//   MinIdx          min with its leftmost index
//   MinCount        min with the number of times it occurs
//   MaxSub          maximum subarray sum
//   Brackets        unmatched brackets; a range is balanced iff it reduces to {0, 0}
//   Hash            polynomial hash and reverse hash (substring equality, palindromes)
//   AffineComp      composition of maps x -> ax + b, applied left to right
//   MatProd         K x K matrix product, for DP transitions over a segment
//   AddMin          range add, range min (AddMax: range max)
//   AddMinCount     range add, range min with count (area of a union of rectangles)
//   SetAdd          range assign and range add, range sum / min / max
//   AffineSum       range x -> ax + b, range sum
//   AddSumSq        range add, range sum and sum of squares
//   PolyAddSum      range add of a degree-K polynomial in the index, range sum
//   XorSum          range xor, range sum
//   BitRuns         range assign / flip on a 0-1 array, count of ones and longest run
//   SetMaxSub       range assign, maximum subarray sum

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// monoids and lazy specs for SegTree / LazySegTree in segment_tree.cpp
// monoid M: T, id(), op(a, b); op is associative and id() is its identity
//   op need not be commutative: SegTree, LazySegTree, DynamicSegTree keep left-to-right order
//   (SegTree2D does not); SparseTable needs op(x, x) = x
// lazy spec S: a monoid plus F, fid(), apply(f, x), compose(f, g), where
//   apply(fid(), x) = x
//   apply(f, op(x, y)) = op(apply(f, x), apply(f, y))
//   compose(f, g) = "g first, then f": apply(compose(f, g), x) = apply(f, apply(g, x))
// every lazy spec here is also a monoid, so it works with SegTree as well
// if apply needs anything besides the answer (the length for sums, the sum of indices, the count of
//   the min, ...), keep it in T too; leaf() builds a single element with length 1, and id() is
//   only for padding, so build the tree from leaf() values instead of using LazySegTree(n)

struct SumM {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
};
struct MinM {
    using T = ll;
    static T id() { return LLONG_MAX; }
    static T op(const T &a, const T &b) { return min(a, b); }
};
struct MaxM {
    using T = ll;
    static T id() { return LLONG_MIN; }
    static T op(const T &a, const T &b) { return max(a, b); }
};
struct GcdM {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return gcd(a, b); }
};
struct XorM {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a ^ b; }
};

// min with its leftmost index; leaves {a[i], i}. for max with leftmost index use {-a[i], i}
struct MinIdx {
    using T = pll;
    static T id() { return {LLONG_MAX, LLONG_MAX}; }
    static T op(const T &a, const T &b) { return min(a, b); }
};

// {min, number of times it occurs}; leaves {a[i], 1}
struct MinCount {
    using T = pll;
    static T id() { return {LLONG_MAX, 0}; }
    static T op(const T &a, const T &b) {
        if (a.first != b.first) return a.first < b.first ? a : b;
        return {a.first, a.second + b.second};
    }
};

// maximum sum of a nonempty subarray; take max(best, 0) if the empty subarray is allowed
struct MaxSub {
    static constexpr ll NEG = LLONG_MIN / 4;
    struct T { ll sum, pre, suf, best, len; };
    static T id() { return {0, NEG, NEG, NEG, 0}; }
    static T leaf(ll x) { return {x, x, x, x, 1}; }
    static T op(const T &a, const T &b) {
        return {a.sum + b.sum, max(a.pre, a.sum + b.pre), max(b.suf, b.sum + a.suf),
                max({a.best, b.best, a.suf + b.pre}), a.len + b.len};
    }
};

// {unmatched ')', unmatched '('}: the range is balanced iff the result is {0, 0}, and its longest
// balanced subsequence has length len - first - second
struct Brackets {
    using T = pll;
    static T id() { return {0, 0}; }
    static T leaf(char c) { return c == '(' ? T{0, 1} : T{1, 0}; }
    static T op(const T &a, const T &b) {
        ll m = min(a.second, b.first);
        return {a.first + b.first - m, a.second + b.second - m};
    }
};

// polynomial hash h, hash of the reversed range r, and B^len; equal strings have equal h,
// and a range is a palindrome iff h == r. V: a ModInt with a large prime modulus
// (e.g. ModInt<(1LL << 61) - 1>); set B to a random value before building
template <class V>
struct Hash {
    static inline V B = 131;
    struct T { V h, r, p; };
    static T id() { return {0, 0, 1}; }
    static T leaf(ll c) { return {c, c, B}; }
    static T op(const T &a, const T &b) { return {a.h * b.p + b.h, b.r * a.p + a.r, a.p * b.p}; }
};

// map x -> first * x + second; query(l, r) is "apply f_l, then f_{l+1}, ..., then f_{r-1}"
template <class V>
struct AffineComp {
    using T = pair<V, V>;
    static T id() { return {1, 0}; }
    static T op(const T &f, const T &g) { return {f.first * g.first, g.first * f.second + g.second}; }
    static V eval(const T &f, const V &x) { return f.first * x + f.second; }
};

// K x K matrix product, left to right: if position i takes a row vector dp to dp * M_i, then
// query(l, r) = M_l * ... * M_{r-1}. for a (max, +) DP, replace + with max and * with + and use
// 0 on the diagonal of id() and -INF elsewhere
template <class V, int K>
struct MatProd {
    using T = array<array<V, K>, K>;
    static T id() {
        T r{};
        for (int i = 0; i < K; i++) r[i][i] = 1;
        return r;
    }
    static T op(const T &a, const T &b) {
        T c{};
        for (int i = 0; i < K; i++)
            for (int k = 0; k < K; k++)
                for (int j = 0; j < K; j++) c[i][j] += a[i][k] * b[k][j];
        return c;
    }
};

// range add, range min / max (the id() checks keep padding at infinity)
struct AddMin : MinM {
    using F = ll;
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return x == LLONG_MAX ? x : x + f; }
    static F compose(const F &f, const F &g) { return f + g; }
};
struct AddMax : MaxM {
    using F = ll;
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return x == LLONG_MIN ? x : x + f; }
    static F compose(const F &f, const F &g) { return f + g; }
};

// range add, range {min, count}; leaves {a[i], 1}. number of zeros in a range of nonnegative
// values: len - (min == 0 ? count : 0), as in the sweep for the area of a union of rectangles
struct AddMinCount : MinCount {
    using F = ll;
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return {x.first == LLONG_MAX ? x.first : x.first + f, x.second}; }
    static F compose(const F &f, const F &g) { return f + g; }
};

// range assign and range add, range sum / min / max
// F = {a, b} is x -> a * x + b with a in {0, 1}: assign v is {0, v}, add v is {1, v}
struct SetAdd {
    struct T { ll sum, mn, mx, len; };
    using F = pll;
    static T id() { return {0, LLONG_MAX, LLONG_MIN, 0}; }
    static T leaf(ll x) { return {x, x, x, 1}; }
    static T op(const T &a, const T &b) { return {a.sum + b.sum, min(a.mn, b.mn), max(a.mx, b.mx), a.len + b.len}; }
    static F fid() { return {1, 0}; }
    static T apply(const F &f, const T &x) {
        if (!x.len) return x;
        if (f.first) return {x.sum + f.second * x.len, x.mn + f.second, x.mx + f.second, x.len};
        return {f.second * x.len, f.second, f.second, x.len};
    }
    static F compose(const F &f, const F &g) { return {f.first * g.first, f.first * g.second + f.second}; }
};

// range x -> a * x + b, range sum; T = {sum, length}, F = {a, b}
// assign v is {0, v}, add v is {1, v}, multiply by v is {v, 0}
template <class V>
struct AffineSum {
    using T = pair<V, V>;
    using F = pair<V, V>;
    static T id() { return {0, 0}; }
    static T leaf(const V &x) { return {x, 1}; }
    static T op(const T &a, const T &b) { return {a.first + b.first, a.second + b.second}; }
    static F fid() { return {1, 0}; }
    static T apply(const F &f, const T &x) { return {f.first * x.first + f.second * x.second, x.second}; }
    static F compose(const F &f, const F &g) { return {f.first * g.first, f.first * g.second + f.second}; }
};

// range add, range sum s1 and sum of squares s2; variance of a range = s2 / len - (s1 / len)^2
template <class V>
struct AddSumSq {
    struct T { V s1, s2, len; };
    using F = V;
    static T id() { return {0, 0, 0}; }
    static T leaf(const V &x) { return {x, x * x, 1}; }
    static T op(const T &a, const T &b) { return {a.s1 + b.s1, a.s2 + b.s2, a.len + b.len}; }
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) {
        return {x.s1 + f * x.len, x.s2 + (f + f) * x.s1 + f * f * x.len, x.len};
    }
    static F compose(const F &f, const F &g) { return f + g; }
};

// range add of a polynomial in the absolute index: a[i] += c[0] + c[1] i + ... + c[K] i^K for
// i in [l, r), range sum. T keeps s[j] = sum of i^j over the segment (s[0] is the length), so
// build leaves with leaf(a[i], i)
// to add p(i - l) instead, e.g. x, x + d, x + 2d, ... starting at l, pass shift({x, d}, l)
// with V = ll, s[K] grows like n^(K+1) / (K+1), so for K >= 2 use ModInt or __int128
template <class V, int K>
struct PolyAddSum {
    using F = array<V, K + 1>;
    struct T { V sum; F s; };
    static T id() { return {0, F{}}; }
    static T leaf(const V &x, ll i) {
        T t{x, F{}};
        V p = 1;
        for (int j = 0; j <= K; j++) t.s[j] = p, p = p * V(i);
        return t;
    }
    static T op(const T &a, const T &b) {
        T c{a.sum + b.sum, a.s};
        for (int j = 0; j <= K; j++) c.s[j] += b.s[j];
        return c;
    }
    static F fid() { return F{}; }
    static T apply(const F &f, const T &x) {
        T y = x;
        for (int j = 0; j <= K; j++) y.sum += f[j] * x.s[j];
        return y;
    }
    static F compose(const F &f, const F &g) {
        F h = f;
        for (int j = 0; j <= K; j++) h[j] += g[j];
        return h;
    }
    static F shift(const F &p, const V &l) {  // coefficients of p(i - l), by Horner, O(K^2)
        F c{};
        for (int k = K; k >= 0; k--) {
            for (int j = K; j > 0; j--) c[j] = c[j - 1] - c[j] * l;
            c[0] = p[k] - c[0] * l;
        }
        return c;
    }
};

// range xor, range sum; T keeps the number of ones in each of the low B bits
template <int B>
struct XorSum {
    struct T { array<int, B> ones; int len; };
    using F = ll;
    static T id() { return {{}, 0}; }
    static T leaf(ll x) {
        T t{{}, 1};
        for (int k = 0; k < B; k++) t.ones[k] = x >> k & 1;
        return t;
    }
    static T op(const T &a, const T &b) {
        T c{{}, a.len + b.len};
        for (int k = 0; k < B; k++) c.ones[k] = a.ones[k] + b.ones[k];
        return c;
    }
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) {
        T y = x;
        for (int k = 0; k < B; k++) if (f >> k & 1) y.ones[k] = x.len - x.ones[k];
        return y;
    }
    static F compose(const F &f, const F &g) { return f ^ g; }
    static ll sum(const T &x) {
        ll s = 0;
        for (int k = 0; k < B; k++) s += (ll)x.ones[k] << k;
        return s;
    }
};

// 0-1 array with range assign and range flip; for each bit v: cnt[v], and the longest run of v
// overall (best[v]), at the start (pre[v]) and at the end (suf[v])
// F = {set, flip}: assign set to the range (unless set == -1), then flip it if flip
struct BitRuns {
    struct T { int len, cnt[2], pre[2], suf[2], best[2]; };
    struct F { int set; bool flip; };
    static T id() { return {}; }
    static T fill(int len, int v) {
        T t{};
        t.len = len;
        t.cnt[v] = t.pre[v] = t.suf[v] = t.best[v] = len;
        return t;
    }
    static T leaf(int v) { return fill(1, v); }
    static T op(const T &a, const T &b) {
        if (!a.len) return b;
        if (!b.len) return a;
        T c{};
        c.len = a.len + b.len;
        for (int v = 0; v < 2; v++) {
            c.cnt[v] = a.cnt[v] + b.cnt[v];
            c.pre[v] = a.pre[v] == a.len ? a.len + b.pre[v] : a.pre[v];
            c.suf[v] = b.suf[v] == b.len ? b.len + a.suf[v] : b.suf[v];
            c.best[v] = max({a.best[v], b.best[v], a.suf[v] + b.pre[v]});
        }
        return c;
    }
    static F fid() { return {-1, false}; }
    static T apply(const F &f, T x) {
        if (!x.len) return x;
        if (f.set != -1) x = fill(x.len, f.set);
        if (f.flip) {
            swap(x.cnt[0], x.cnt[1]);
            swap(x.pre[0], x.pre[1]);
            swap(x.suf[0], x.suf[1]);
            swap(x.best[0], x.best[1]);
        }
        return x;
    }
    static F compose(const F &f, const F &g) { return f.set != -1 ? f : F{g.set, g.flip != f.flip}; }
};

// range assign, maximum subarray sum (uses MaxSub above); F = value to assign, or NONE
struct SetMaxSub : MaxSub {
    static constexpr ll NONE = LLONG_MIN;
    using F = ll;
    static F fid() { return NONE; }
    static T apply(const F &f, const T &x) {
        if (f == NONE || !x.len) return x;
        ll s = f * x.len, m = f > 0 ? s : f;
        return {s, m, m, m, x.len};
    }
    static F compose(const F &f, const F &g) { return f == NONE ? g : f; }
};
