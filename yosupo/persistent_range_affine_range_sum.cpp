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

    ModInt(ll v = 0): val(v %mod()) { if (val < 0) val += mod(); }

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

using mint = ModInt<MOD>;

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

// persistent lazy segment tree, range update and query on [l, r); version 0 is the built array
// a node's tag is always newer than everything below it, so queries apply tags on the way up and allocate nothing;
// updates hand pending tags down to fresh copies of the children, so F does not need to be commutative
// PersistentLazySegTree<S>: works with any S shaped like Spec above
//   PersistentLazySegTree(n)    version 0 is n identity elements, O(n)
//   PersistentLazySegTree(a)    version 0 is a, O(n)
//   update(ver, l, r, f)        apply f to every element of [l, r) on a copy of ver, returns the new version, O(log n) time and memory
//   copy_range(ver, src, l, r)  a copy of ver with [l, r) taken from version src, returns the new version, O(log n) time and memory
//   get(ver, p)                 a[p] in ver, O(log n)
//   query(ver, l, r)            op over [l, r) in ver, O(log n)
template <class S>
struct PersistentLazySegTree {
    using T = typename S::T;
    using F = typename S::F;
    struct Node { int l, r; T val; F lz; };
    int n;
    vector<Node> t;  // t[0] is a placeholder, used only as the root when n = 0
    vector<int> roots;

    PersistentLazySegTree(int n = 0): PersistentLazySegTree(vector<T>(n, S::id())) {}

    PersistentLazySegTree(const vector<T> &a): n(a.size()), t(1, Node{0, 0, S::id(), S::fid()}), roots(1, 0) {
        if (n) roots[0] = build(a, 0, n);
    }

    int build(const vector<T> &a, int lo, int hi) {
        if (hi - lo == 1) {
            t.push_back({0, 0, a[lo], S::fid()});
            return t.size() - 1;
        }
        int mid = (lo + hi) / 2;
        int l = build(a, lo, mid), r = build(a, mid, hi);
        t.push_back({l, r, S::op(t[l].val, t[r].val), S::fid()});
        return t.size() - 1;
    }

    int applied(int x, const F &f) {  // a copy of node x with f applied to its whole subtree
        Node cur = t[x];
        cur.val = S::apply(f, cur.val);
        cur.lz = S::compose(f, cur.lz);
        t.push_back(cur);
        return t.size() - 1;
    }

    int update(int ver, int l, int r, const F &f) {
        roots.push_back(l < r && n ? update_node(roots[ver], 0, n, l, r, f, S::fid()) : roots[ver]);
        return roots.size() - 1;
    }

    // g is the pending tag from the ancestors, which is newer than anything stored in x's subtree
    int update_node(int x, int lo, int hi, int l, int r, const F &f, const F &g) {
        if (r <= lo || hi <= l) return applied(x, g);
        if (l <= lo && hi <= r) return applied(x, S::compose(f, g));
        Node cur = t[x];
        F h = S::compose(g, cur.lz);
        int mid = (lo + hi) / 2;
        cur.l = update_node(cur.l, lo, mid, l, r, f, h);
        cur.r = update_node(cur.r, mid, hi, l, r, f, h);
        cur.val = S::op(t[cur.l].val, t[cur.r].val);
        cur.lz = S::fid();
        t.push_back(cur);
        return t.size() - 1;
    }

    int copy_range(int ver, int src, int l, int r) {
        roots.push_back(l < r && n ? copy_node(roots[ver], roots[src], 0, n, l, r, S::fid(), S::fid()) : roots[ver]);
        return roots.size() - 1;
    }

    // walks both trees together; gx and gy are the pending tags from the ancestors of x (in ver) and y (in src)
    int copy_node(int x, int y, int lo, int hi, int l, int r, const F &gx, const F &gy) {
        if (r <= lo || hi <= l) return applied(x, gx);
        if (l <= lo && hi <= r) return applied(y, gy);
        Node cur = t[x];
        F hx = S::compose(gx, t[x].lz), hy = S::compose(gy, t[y].lz);
        int mid = (lo + hi) / 2, yl = t[y].l, yr = t[y].r;
        cur.l = copy_node(cur.l, yl, lo, mid, l, r, hx, hy);
        cur.r = copy_node(cur.r, yr, mid, hi, l, r, hx, hy);
        cur.val = S::op(t[cur.l].val, t[cur.r].val);
        cur.lz = S::fid();
        t.push_back(cur);
        return t.size() - 1;
    }

    T get(int ver, int p) const { return query(ver, p, p + 1); }

    T query(int ver, int l, int r) const { return query_node(roots[ver], 0, n, l, r); }

    T query_node(int x, int lo, int hi, int l, int r) const {
        if (r <= lo || hi <= l) return S::id();
        if (l <= lo && hi <= r) return t[x].val;
        int mid = (lo + hi) / 2;
        return S::apply(t[x].lz, S::op(query_node(t[x].l, lo, mid, l, r), query_node(t[x].r, mid, hi, l, r)));
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    using S = AffineSum<mint>;
    vector<S::T> a(n);
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        a[i] = S::leaf(x);
    }
    PersistentLazySegTree<S> tree(a);
    vector<int> ver(q + 1, 0);  // ver[i + 1] = tree version of A_i; ver[0] is the initial array A_-1
    for (ll i = 0; i < q; i++) {
        ll type, k;
        cin >> type >> k;
        if (type == 0) {
            ll l, r, b, c;
            cin >> l >> r >> b >> c;
            ver[i + 1] = tree.update(ver[k + 1], l, r, {b, c});
        }
        else if (type == 1) {
            ll s, l, r;
            cin >> s >> l >> r;
            ver[i + 1] = tree.copy_range(ver[k + 1], ver[s + 1], l, r);
        }
        else {
            ll l, r;
            cin >> l >> r;
            cout << tree.query(ver[k + 1], l, r).first << "\n";
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
