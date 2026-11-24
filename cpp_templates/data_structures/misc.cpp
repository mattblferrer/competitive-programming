// Contents
//   Compressor      coordinate compression
//   MinStack        stack with minimum query
//   MinQueue        queue with minimum query
//   MisofTree       multiset of integers in [0, 2^BITS)

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

// multiset of integers in [0, 2^BITS)
//   insert(x)    add one copy of x, O(BITS)
//   erase(x)     remove one copy of x; x must be present, O(BITS)
//   nth(k)       k-th smallest element (0-indexed); requires k < size, O(BITS)
//   rank(x)      number of elements < x, for x < 2^BITS, O(BITS); with nth: successor = nth(rank(x)), predecessor = nth(rank(x + 1) - 1)
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
