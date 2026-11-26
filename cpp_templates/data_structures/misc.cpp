// Contents
//   Compressor       coordinate compression
//   MinStack         stack with minimum query
//   MinQueue         queue with minimum query
//   FoldDeque        deque with the fold of a monoid over all its elements in order (two stacks)
//   PersistentQueue  persistent queue: every push and pop makes a new version, O(1) memory per push
//   MisofTree        multiset of integers in [0, 2^BITS)
//   RangeMode        static range mode, online: a mode of a[l, r) and its count (sqrt decomposition), O(sqrt n) per query

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// coordinate compression
//   Compressor(a)   sorted distinct values of a, O(n log n)
//   id(x)           index of x, or of the first value above x if x is absent, O(log n)
//   val(i)          the i-th smallest distinct value, O(1)
//   size()          number of distinct values, O(1)
template <class T>
struct Compressor {
    vector<T> v;

    Compressor(vector<T> a = {}): v(move(a)) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    int id(const T &x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); }
    T val(int i) const { return v[i]; }
    int size() const { return v.size(); }
};

// stack with minimum query
//   empty()    true if the stack is empty, O(1)
//   push(x)    push x, O(1)
//   pop()      pop the top, O(1)
//   top()      top element, O(1)
//   min()      smallest element in the stack, O(1)
struct MinStack {
    vector<pll> st;  // {value, min up to here}

    bool empty() const { return st.empty(); }
    void push(ll x) { st.push_back({x, st.empty() ? x : std::min(x, st.back().second)}); }
    void pop() { st.pop_back(); }
    ll top() const { return st.back().first; }
    ll min() const { return st.back().second; }
};

// queue with minimum query
//   empty()    true if the queue is empty, O(1)
//   push(x)    push x at the back, O(1)
//   pop()      pop the front, O(1) amortized
//   front()    front element, O(1) amortized
//   min()      smallest element in the queue, O(1)
struct MinQueue {
    MinStack in, out;

    void flip() {
        if (!out.empty()) return;
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }

    bool empty() const { return in.empty() && out.empty(); }
    void push(ll x) { in.push(x); }
    void pop() { flip(); out.pop(); }
    ll front() { flip(); return out.top(); }

    ll min() const {
        if (in.empty()) return out.min();
        if (out.empty()) return in.min();
        return std::min(in.min(), out.min());
    }
};

// deque with the fold of a monoid M (like the ones in monoids.cpp) over all its elements, front to back
// two stacks, each keeping the fold of everything below; an empty side takes half of the other
// as a queue (push_back, pop_front) it is the classic two-stack queue
//   push_front(x), push_back(x)   add x at that end, O(1)
//   pop_front(), pop_back()       remove from that end; the deque must not be empty, O(1) amortized
//   fold()                        op over all elements from front to back, M::id() if empty, O(1)
//   size()                        number of elements, O(1)
template <class M>
struct FoldDeque {
    using T = typename M::T;
    vector<T> fv, fa, bv, ba;  // front stack (top = front) and back stack (top = back): values and folds

    void push_front(const T &x) {
        fv.push_back(x);
        fa.push_back(M::op(x, fa.empty() ? M::id() : fa.back()));
    }

    void push_back(const T &x) {
        bv.push_back(x);
        ba.push_back(M::op(ba.empty() ? M::id() : ba.back(), x));
    }

    void rebuild(bool front) {  // split all elements in half between the two stacks
        vector<T> all(fv.rbegin(), fv.rend());
        all.insert(all.end(), bv.begin(), bv.end());
        fv.clear(), fa.clear(), bv.clear(), ba.clear();
        int k = all.size(), m = front ? (k + 1) / 2 : k / 2;  // the side being popped gets at least one
        for (int i = m - 1; i >= 0; i--) push_front(all[i]);
        for (int i = m; i < k; i++) push_back(all[i]);
    }

    void pop_front() {
        if (fv.empty()) rebuild(true);
        fv.pop_back(), fa.pop_back();
    }

    void pop_back() {
        if (bv.empty()) rebuild(false);
        bv.pop_back(), ba.pop_back();
    }

    T fold() const { return M::op(fa.empty() ? M::id() : fa.back(), ba.empty() ? M::id() : ba.back()); }

    int size() const { return fv.size() + bv.size(); }
};

// persistent queue: push and pop make a new version and leave the old ones unchanged; version 0 is empty
// every element ever pushed is a node of a tree whose parent is the back of the version it was pushed onto;
// a version is {back node, size}, and its front is the ancestor of the back node at depth dep(back) - size + 1,
// found in O(log n) with skew-binary jump pointers (Myers), so each node costs O(1) memory
//   push(ver, x)    x pushed at the back of ver, returns the new version, O(1)
//   pop(ver)        ver without its front; ver must not be empty, returns the new version, O(1)
//   front(ver)      front element of ver; ver must not be empty, O(log n)
//   back(ver)       back element of ver; ver must not be empty, O(1)
//   size(ver)       number of elements in ver, O(1)
template <class T>
struct PersistentQueue {
    struct Node { int par, jump, dep; T val; };
    vector<Node> t{{0, 0, 0, T()}};  // t[0] is the root, below every element
    vector<pair<int, int>> vers{{0, 0}};  // {back node, size}

    int push(int ver, const T &x) {
        int p = vers[ver].first, j = t[p].jump;
        int jump = t[p].dep - t[j].dep == t[j].dep - t[t[j].jump].dep ? t[j].jump : p;
        t.push_back({p, jump, t[p].dep + 1, x});
        vers.push_back({(int)t.size() - 1, vers[ver].second + 1});
        return vers.size() - 1;
    }

    int pop(int ver) {
        vers.push_back({vers[ver].first, vers[ver].second - 1});
        return vers.size() - 1;
    }

    T front(int ver) const {
        auto [u, s] = vers[ver];
        int d = t[u].dep - s + 1;
        while (t[u].dep > d) u = t[t[u].jump].dep < d ? t[u].par : t[u].jump;
        return t[u].val;
    }

    T back(int ver) const { return t[vers[ver].first].val; }
    int size(int ver) const { return vers[ver].second; }
};

// multiset of integers in [0, 2^BITS)
//   insert(x)    add one copy of x, O(BITS)
//   erase(x)     remove one copy of x; x must be present, O(BITS)
//   nth(k)       k-th smallest element (0-indexed); requires k < size, O(BITS)
//   rank(x)      number of elements < x, for x < 2^BITS, O(BITS);
//                with nth: successor = nth(rank(x)), predecessor = nth(rank(x + 1) - 1)
//   cnt[0][x]    number of copies of x
template <int BITS = 20>
struct MisofTree {
    vector<vector<int>> cnt;

    MisofTree(): cnt(BITS) {
        for (int i = 0; i < BITS; i++) cnt[i].assign(1 << (BITS - i), 0);
    }

    void insert(int x) {
        for (int i = 0; i < BITS; i++, x >>= 1) cnt[i][x]++;
    }

    void erase(int x) {
        for (int i = 0; i < BITS; i++, x >>= 1) cnt[i][x]--;
    }

    int nth(int k) const {
        int res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            res <<= 1;
            if (cnt[i][res] <= k) {
                k -= cnt[i][res];
                res |= 1;
            }
        }
        return res;
    }

    int rank(int x) const {
        int res = 0;
        for (int i = 0; i < BITS; i++, x >>= 1) if (x & 1) res += cnt[i][x - 1];  // the left sibling is all smaller
        return res;
    }
};

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
