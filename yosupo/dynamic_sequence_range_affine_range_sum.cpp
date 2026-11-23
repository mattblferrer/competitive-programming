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

// implicit treap: an array supporting insert/erase at any position, range update, range reverse and range fold
// (0-indexed); ImplicitTreap<S> takes a lazy spec S shaped like LazySegTree's (ready-made ones in monoids.cpp,
// and NoUpdate<M> there turns any monoid M into one); insert S::leaf(x) when apply needs the length
// each node keeps its subtree's fold in both directions, so reverse also works when op is not commutative
//   insert(p, v)      insert v so that it becomes a[p], O(log n) expected
//   erase(p)          remove a[p], O(log n) expected
//   get(p)            a[p], O(log n) expected
//   query(l, r)       op over a[l..r), O(log n) expected
//   update(l, r, f)   apply f to every element of a[l..r), O(log n) expected
//   reverse(l, r)     reverse a[l..r), O(log n) expected
//   size()            current length, O(1)
template <class S>
struct ImplicitTreap {
    using T = typename S::T;
    using F = typename S::F;
    struct Node {
        T val, sum, rsum;  // rsum = op over the subtree from right to left
        F lz;  // v's own val, sum, rsum already include lz; its children still need it
        unsigned pri;
        int sz, l, r;
        bool rev;  // v's own children are already swapped; rev means its children still need flipping
    };
    vector<Node> t;  // t[0] is the null node
    int root = 0;
    mt19937 gen{(unsigned)chrono::steady_clock::now().time_since_epoch().count()};

    ImplicitTreap(): t(1, Node{S::id(), S::id(), S::id(), S::fid(), 0, 0, 0, 0, false}) {}

    void apply(int v, const F &f) {
        if (!v) return;
        t[v].val = S::apply(f, t[v].val);
        t[v].sum = S::apply(f, t[v].sum);
        t[v].rsum = S::apply(f, t[v].rsum);
        t[v].lz = S::compose(f, t[v].lz);
    }

    void flip(int v) {
        if (!v) return;
        swap(t[v].l, t[v].r);
        swap(t[v].sum, t[v].rsum);
        t[v].rev = !t[v].rev;
    }

    void push(int v) {
        apply(t[v].l, t[v].lz);
        apply(t[v].r, t[v].lz);
        t[v].lz = S::fid();
        if (t[v].rev) {
            flip(t[v].l);
            flip(t[v].r);
            t[v].rev = false;
        }
    }

    void pull(int v) {
        int l = t[v].l, r = t[v].r;
        t[v].sz = t[l].sz + 1 + t[r].sz;
        t[v].sum = S::op(S::op(t[l].sum, t[v].val), t[r].sum);
        t[v].rsum = S::op(S::op(t[r].rsum, t[v].val), t[l].rsum);
    }

    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].pri > t[b].pri) {
            push(a);
            t[a].r = merge(t[a].r, b);
            pull(a);
            return a;
        }
        push(b);
        t[b].l = merge(a, t[b].l);
        pull(b);
        return b;
    }

    // a gets the first k elements of v, b gets the rest
    void split(int v, int k, int &a, int &b) {
        if (!v) {
            a = b = 0;
            return;
        }
        push(v);
        if (k <= t[t[v].l].sz) {
            split(t[v].l, k, a, t[v].l);
            b = v;
        } else {
            split(t[v].r, k - t[t[v].l].sz - 1, t[v].r, b);
            a = v;
        }
        pull(v);
    }

    void insert(int p, const T &v) {
        t.push_back({v, v, v, S::fid(), gen(), 1, 0, 0, false});
        int a, b, id = t.size() - 1;
        split(root, p, a, b);
        root = merge(merge(a, id), b);
    }

    void erase(int p) {
        int a, b, c;
        split(root, p + 1, a, c);
        split(a, p, a, b);
        root = merge(a, c);
    }

    T get(int p) {
        int v = root;
        while (true) {
            push(v);
            int left = t[t[v].l].sz;
            if (p < left) {
                v = t[v].l;
            } else if (p == left) {
                return t[v].val;
            } else {
                p -= left + 1;
                v = t[v].r;
            }
        }
    }

    T query(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        T res = t[b].sum;
        root = merge(merge(a, b), c);
        return res;
    }

    void update(int l, int r, const F &f) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        apply(b, f);
        root = merge(merge(a, b), c);
    }

    void reverse(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        flip(b);
        root = merge(merge(a, b), c);
    }

    int size() const { return t[root].sz; }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    using S = AffineSum<mint>;
    ImplicitTreap<S> treap;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        treap.insert(i, S::leaf(ai));
    }

    for (ll qi = 0; qi < q; qi++) {
        ll type;
        cin >> type;
        if (type == 0) {
            ll i, x;
            cin >> i >> x;
            treap.insert(i, S::leaf(x));
        }
        else if (type == 1) {
            ll i;
            cin >> i;
            treap.erase(i);
        }
        else if (type == 2) {
            ll l, r;
            cin >> l >> r;
            treap.reverse(l, r);
        }
        else if (type == 3) {
            ll l, r, b, c;
            cin >> l >> r >> b >> c;
            treap.update(l, r, {b, c});
        }
        else {
            ll l, r;
            cin >> l >> r;
            cout << treap.query(l, r).first << "\n";
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
