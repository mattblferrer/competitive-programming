// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998244353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// compile-time modulus: using mint = ModInt<1'000'000'007>;
//   each modulus is its own type, so mixing two moduli is a compile error.
// runtime modulus: use a non-positive id, e.g. using dmint = ModInt<0>;
//   then call dmint::set_mod(p) before use (ModInt<-1>, ModInt<-2>, ... for more).
// inv() works for any modulus coprime to val (prime not required).
//   mod()                      current modulus, O(1)
//   set_mod(m)                 set the runtime modulus (MOD <= 0 only), O(1)
//   mul(a, b)                  a * b % mod(), O(1)
//   ModInt(v)                  v % mod(), normalized to [0, mod()), O(1)
//   pow(e)                     this^e, O(log e)
//   inv()                      modular inverse via extended Euclid, O(log mod()); requires gcd(val, mod()) = 1
//   +, -, *, / (and +=, ...)   arithmetic, O(1) (division is O(log mod()))
// friends so that e.g. 2 + x and 1 - x also work
template <ll MOD>
struct ModInt {
    ll val;
    static inline ll dyn = 1;  // runtime modulus (only used when MOD <= 0)
    static inline ull im = 0;  // Barrett constant for the runtime modulus

    static constexpr bool is_static = MOD > 0;
    static ll mod() {
        if constexpr (is_static) return MOD;
        else return dyn;
    }
    static void set_mod(ll m) {
        dyn = m;
        im = ~0ULL / m + 1;
    }
    static ll mul(ll a, ll b) {
        if constexpr (is_static) {
            if constexpr (MOD < (1LL << 31)) return a * b % MOD;
            else return (__int128)a * b % MOD;
        }
        else if (dyn < (1LL << 31)) {  // Barrett reduction, avoids slow % by a variable
            ull z = (ull)a * b;
            ull x = (ull)(((unsigned __int128)z * im) >> 64), y = x * dyn;
            return z - y + (z < y ? dyn : 0);
        }
        else return (__int128)a * b % dyn;
    }

    ModInt(ll v = 0): val(v % mod()) { if (val < 0) val += mod(); }

    ModInt pow(ll e) const {
        ModInt r = 1, b = *this;
        for (; e > 0; e >>= 1, b *= b) if (e & 1) r *= b;
        return r;
    }
    ModInt inv() const {
        ll a = val, b = mod(), x = 1, y = 0;
        while (b) {
            ll q = a / b;
            swap(a -= q * b, b);
            swap(x -= q * y, y);
        }
        assert(a == 1);  // inverse doesn't exist if gcd(val, mod()) != 1
        return ModInt(x);
    }

    ModInt &operator+=(const ModInt &o) { if ((val += o.val) >= mod()) val -= mod(); return *this; }
    ModInt &operator-=(const ModInt &o) { if ((val -= o.val) < 0) val += mod(); return *this; }
    ModInt &operator*=(const ModInt &o) { val = mul(val, o.val); return *this; }
    ModInt &operator/=(const ModInt &o) { return *this *= o.inv(); }
    ModInt operator-() const { return ModInt() - *this; }
    ModInt &operator++() { return *this += 1; }
    ModInt &operator--() { return *this -= 1; }
    ModInt operator++(int) { ModInt t = *this; ++*this; return t; }
    ModInt operator--(int) { ModInt t = *this; --*this; return t; }

    friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt &b) { return a /= b; }
    friend bool operator==(const ModInt &a, const ModInt &b) { return a.val == b.val; }
    friend bool operator!=(const ModInt &a, const ModInt &b) { return a.val != b.val; }
    friend ostream &operator<<(ostream &os, const ModInt &m) { return os << m.val; }
    friend istream &operator>>(istream &is, ModInt &m) { ll x; is >> x; m = ModInt(x); return is; }
};

// SegTree<M>: works with any monoid M shaped like Monoid above
//   SegTree(n)    n identity elements, O(n)
//   SegTree(a)    build from a, O(n)
//   set(p, v)     a[p] = v, O(log n)
//   get(p)        a[p], O(1)
//   query(l, r)   op over [l, r), O(log n)
template <class M>
struct SegTree {
    using T = typename M::T;
    int n;
    vector<T> t;

    SegTree(int n = 0): n(n), t(2 * n, M::id()) {}

    SegTree(const vector<T> &a): n(a.size()), t(2 * a.size(), M::id()) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = M::op(t[2 * i], t[2 * i + 1]);
    }

    void set(int p, T v) {
        for (t[p += n] = v; p > 1; p >>= 1)
            t[p >> 1] = M::op(t[p & ~1], t[p | 1]);
    }

    T get(int p) const { return t[p + n]; }

    T query(int l, int r) const {
        T L = M::id(), R = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = M::op(L, t[l++]);
            if (r & 1) R = M::op(t[--r], R);
        }
        return M::op(L, R);
    }
};

// map x -> first * x + second; query(l, r) is "apply f_l, then f_{l+1}, ..., then f_{r-1}"
template <class V>
struct AffineComp {
    using T = pair<V, V>;
    static T id() { return {1, 0}; }
    static T op(const T &f, const T &g) { return {f.first * g.first, g.first * f.second + g.second}; }
    static V eval(const T &f, const V &x) { return f.first * x + f.second; }
};

// sortable segment tree: a sequence of (key, value) pairs with point set, sorting a range by key and folding a range,
// for any monoid M (op need not commute), using SegTree above; keys are ints in [0, K) (compress them), distinct
// among the current elements. the sequence is kept as runs sorted by key, each a segment tree over the keys holding
// its fold in both key orders, and the outer SegTree holds each run's fold at its first position; sorting merges
// runs (segment tree merge), and a run is cut in two by rank where an operation starts or ends
// amortized O(log n + log K) per call, O((n + q) log K) memory
//   SortableSegTree(K, key, val)   element i is (key[i], val[i]), O(n log K)
//   set(i, k, v)                   element i becomes (k, v)
//   sort(l, r, desc)               sort [l, r) by key, increasing (decreasing if desc)
//   query(l, r)                    op over [l, r) in the current order
template <class M>
struct SortableSegTree {
    using T = typename M::T;
    struct Node { int l, r, cnt; T fwd, bwd; };  // fold in increasing / decreasing key order
    int n, K;
    vector<Node> t;  // t[0] is the empty node
    vector<int> freed, root;  // root[s] = key tree of the run starting at s
    vector<char> desc;
    std::set<int> starts;
    SegTree<M> outer;

    SortableSegTree(int K, const vector<int> &key, const vector<T> &val)
        : n(key.size()), K(K), t(1, Node{0, 0, 0, M::id(), M::id()}), root(n), desc(n, 0), outer(val) {
        for (int i = 0; i < n; i++) {
            root[i] = leaf(key[i], val[i]);
            starts.insert(i);
        }
    }

    int alloc() {
        if (freed.empty()) {
            t.push_back(t[0]);
            return t.size() - 1;
        }
        int x = freed.back();
        freed.pop_back();
        t[x] = t[0];
        return x;
    }

    void release(int x) {
        if (!x) return;
        release(t[x].l);
        release(t[x].r);
        freed.push_back(x);
    }

    int leaf(int k, const T &v) {  // a key tree with the single element (k, v)
        int res = alloc(), x = res;
        for (int lo = 0, hi = K;;) {
            t[x].cnt = 1;
            t[x].fwd = t[x].bwd = v;
            if (hi - lo == 1) return res;
            int mid = (lo + hi) / 2, c = alloc();
            if (k < mid) t[x].l = c, hi = mid;
            else t[x].r = c, lo = mid;
            x = c;
        }
    }

    void pull(int x) {
        const Node &a = t[t[x].l], &b = t[t[x].r];
        t[x].cnt = a.cnt + b.cnt;
        t[x].fwd = M::op(a.fwd, b.fwd);
        t[x].bwd = M::op(b.bwd, a.bwd);
    }

    int merge(int a, int b) {  // the keys are distinct, so two leaves never meet
        if (!a || !b) return a | b;
        t[a].l = merge(t[a].l, t[b].l);
        t[a].r = merge(t[a].r, t[b].r);
        freed.push_back(b);
        pull(a);
        return a;
    }

    pair<int, int> split(int a, int k) {  // {the k smallest keys, the rest}
        if (!a || k <= 0) return {0, a};
        if (k >= t[a].cnt) return {a, 0};
        int b = alloc(), c = t[a].l;
        if (k <= t[c].cnt) {
            auto [x, y] = split(c, k);
            t[b].l = y, t[b].r = t[a].r, t[a].l = x, t[a].r = 0;
        } else {
            auto [x, y] = split(t[a].r, k - t[c].cnt);
            t[b].r = y, t[a].r = x;
        }
        pull(a);
        pull(b);
        return {a, b};
    }

    T fold(int s) const { return desc[s] ? t[root[s]].bwd : t[root[s]].fwd; }

    void cut(int i) {  // make a run start at i
        if (i >= n || starts.count(i)) return;
        int s = *prev(starts.upper_bound(i)), k = i - s;
        auto [x, y] = split(root[s], desc[s] ? t[root[s]].cnt - k : k);
        if (desc[s]) swap(x, y);  // a decreasing run keeps its largest keys first
        root[s] = x, root[i] = y, desc[i] = desc[s];
        starts.insert(i);
        outer.set(s, fold(s));
        outer.set(i, fold(i));
    }

    void set(int i, int k, const T &v) {
        cut(i);
        cut(i + 1);
        release(root[i]);
        root[i] = leaf(k, v);
        desc[i] = 0;
        outer.set(i, v);
    }

    void sort(int l, int r, bool d = false) {
        if (l >= r) return;
        cut(l);
        cut(r);
        for (auto it = starts.upper_bound(l); it != starts.end() && *it < r; it = starts.erase(it)) {
            root[l] = merge(root[l], root[*it]);
            outer.set(*it, M::id());
        }
        desc[l] = d;
        outer.set(l, fold(l));
    }

    T query(int l, int r) {
        cut(l);
        cut(r);
        return outer.query(l, r);
    }
};

using mint = ModInt<998'244'353>;
using F = AffineComp<mint>;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> p(n);
    vector<F::T> f(n);
    for (ll i = 0; i < n; i++) cin >> p[i] >> f[i].first >> f[i].second;

    vector<array<ll, 5>> qs(q); 
    vector<ll> keys = p;
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 0) {
            ll pos, k, a, b;
            cin >> pos >> k >> a >> b;
            qs[i] = {type, pos, k, a, b};
            keys.push_back(k);
        }
        if (type == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            qs[i] = {type, l, r, x, 0};
        }
        if (type == 2 || type == 3) {
            ll l, r;
            cin >> l >> r;
            qs[i] = {type, l, r, 0, 0};
        }
    }

    sort(keys.begin(), keys.end());
    auto id = [&](ll x) { return int(lower_bound(keys.begin(), keys.end(), x) - keys.begin()); };
    vector<int> key(n);
    for (ll i = 0; i < n; i++) key[i] = id(p[i]);
    SortableSegTree<F> st(keys.size(), key, f);
    
    for (ll i = 0; i < q; i++) {
        ll type = qs[i][0];
        if (type == 0) {
            ll pos = qs[i][1], k = qs[i][2], a = qs[i][3], b = qs[i][4];
            st.set(pos, id(k), {a, b});
        }
        if (type == 1) {
            ll l = qs[i][1], r = qs[i][2], x = qs[i][3];
            cout << F::eval(st.query(l, r), mint(x)) << "\n";
        }
        if (type == 2) {
            ll l = qs[i][1], r = qs[i][2];
            st.sort(l, r, false);
        }
        if (type == 3) {
            ll l = qs[i][1], r = qs[i][2];
            st.sort(l, r, true);
        }
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
